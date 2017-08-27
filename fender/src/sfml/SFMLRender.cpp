//
// Created by ganz on 28/07/17.
//

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SFMLRender.hpp"
#include "flog.hpp"

extern "C" fender::SFMLRender* create()
{
    return new fender::SFMLRender();
}

fender::SFMLRender::SFMLRender()
{

}

void    fender::SFMLRender::openWindow()
{
    auto mode = sf::VideoMode::getDesktopMode();
    auto windowStyle = static_cast<int>(sf::Style::None);
    if (this->_resizable)
        windowStyle |= sf::Style::Resize;
    if (this->_windowStyle != fender::WindowStyle::BORDERLESS)
        windowStyle |= sf::Style::Titlebar | sf::Style::Close;
    if (this->_windowStyle == fender::WindowStyle::FULLSCREEN)
        windowStyle |= sf::Style::Fullscreen;
    int xAlign = 0;
    int yAlign = 0;
    if (_windowAlign.X == fender::Align::CENTER)
        xAlign = mode.width / 2 - this->_windowSize.X / 2;
    if (_windowAlign.Y == fender::Align::CENTER)
        yAlign = mode.height / 2 - this->_windowSize.Y / 2;
    if (_windowAlign.X == fender::Align::RIGHT)
        xAlign = mode.width - this->_windowSize.X;
    if (_windowAlign.Y == fender::Align::BOTTOM)
        yAlign = mode.width - this->_windowSize.Y;
    this->win.create(sf::VideoMode(this->_windowSize.X, this->_windowSize.Y),
                     this->_windowName, windowStyle);
    this->win.setPosition(sf::Vector2i(xAlign, yAlign));
    this->initFactory();
}

void    fender::SFMLRender::initFactory()
{
    this->elementFactory["AnimatedImage"] = [this](fender::Element &src)
    {
        auto *obj = dynamic_cast<fender::AnimatedImage *>(&src);
        if (obj)
            this->create<types::AnimatedImage>(*obj);
    };
    this->elementFactory["Bar"] = [this](fender::Element &src)
    {
        auto *obj = dynamic_cast<fender::Bar *>(&src);
        if (obj)
            this->create<types::Bar>(*obj);
    };
    this->elementFactory["Button"] = [this](fender::Element &src)
    {
        auto *obj = dynamic_cast<fender::Button *>(&src);
        if (obj)
            this->create<types::Button>(*obj);
    };
    this->elementFactory["Popup"] = [this](fender::Element &src)
    {
        auto *obj = dynamic_cast<fender::Popup *>(&src);
        if (obj)
            this->create<types::Popup>(*obj);
    };
}

void    fender::SFMLRender::closeWindow()
{

}

bool    fender::SFMLRender::isRunning()
{
    return this->win.isOpen();
}

void    fender::SFMLRender::refresh()
{
    this->win.clear(sf::Color::Black);
    if (this->currentLayout->isVisible())
    {
        for (auto &pair: this->elements)
        {
            auto &elem = *pair.second;
            elem.update();
            if (!elem.src.isVisible())
                continue ;
            elem.draw(this->win);
        }
    }
    this->win.display();

    while (this->win.pollEvent(this->events))
    {
        if (this->events.type == sf::Event::Closed)
            this->win.close();
        if (this->events.type == sf::Event::KeyPressed)
        {
            if (this->events.key.code == sf::Keyboard::Return)
            {
                std::cout << "the escape key was pressed" << std::endl;
                std::cout << "control:" << this->events.key.control << std::endl;
                std::cout << "alt:" << this->events.key.alt << std::endl;
                std::cout << "shift:" << this->events.key.shift << std::endl;
                std::cout << "system:" << this->events.key.system << std::endl;
                this->win.close();
            }
        }
    }
}

void    fender::SFMLRender::resize(int x, int y)
{
    this->win.setSize(sf::Vector2u(x, y));
}

void    fender::SFMLRender::write(int x, int y, std::string const &msg)
{

}

void    fender::SFMLRender::loadCurrentLayout()
{
    fonts["jedi"].loadFromFile("assets/fonts/jedi.ttf");
    fonts["pixel"].loadFromFile("assets/fonts/pixel.ttf");
    fonts["game"].loadFromFile("assets/fonts/game.ttf");
    for (auto const &pair: this->currentLayout->getElements())
    {
        LOUT("SFMLRender:\tLoading " + pair.second->getType() + " " + pair.second->getName());
        this->elementFactory[pair.second->getType()](*pair.second);
    }
}
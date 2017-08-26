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

//    if (!this->texture.loadFromFile("assets/images/fengine.png"))
//    {
//        LERR("Cannot load file fengine.png");
//    }
//    this->electricityTexture.loadFromFile("assets/textures/electricity.jpg");
//    this->logo.setTexture(this->texture);
//    this->texture.setSmooth(true);
//    this->back.setFillColor(sf::Color::White);
//    this->prog.setTexture(&this->electricityTexture);
//    this->back.setPosition(200, 320);
//    this->prog.setPosition(200, 320);
//    this->logo.setPosition(85, -55);
//    this->logo.setScale(sf::Vector2f{0.3, 0.3});
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
    // draw everything here...
//    this->win.draw(this->logo);
//    this->win.draw(this->back);
//    this->win.draw(this->prog);
    // end the current frame
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

//    this->prog.setSize(sf::Vector2f(this->progress * 250.0 / 100.0, 10));
//    this->progress += 0.1;
//    if (this->progress >= 100)
//        this->win.close();
}

void    fender::SFMLRender::resize(int x, int y)
{
    this->win.setSize(sf::Vector2u(x, y));
}

void    fender::SFMLRender::write(int x, int y, std::string const &msg)
{

}
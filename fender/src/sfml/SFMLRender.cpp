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

static std::unordered_map<sf::Keyboard::Key, fender::Input> fenderCodes =
        {
               {sf::Keyboard::Escape, fender::Input::Escape},
               {sf::Keyboard::Space, fender::Input::Space},
               {sf::Keyboard::LControl, fender::Input::LCtrl},
               {sf::Keyboard::RControl, fender::Input::RCtrl},
               {sf::Keyboard::LAlt, fender::Input::Alt},
               {sf::Keyboard::LShift, fender::Input::LShift},
               {sf::Keyboard::F1, fender::Input::F1},
               {sf::Keyboard::F2, fender::Input::F2},
               {sf::Keyboard::F3, fender::Input::F3},
               {sf::Keyboard::F4, fender::Input::F4},
               {sf::Keyboard::F5, fender::Input::F5},
               {sf::Keyboard::F6, fender::Input::F6},
               {sf::Keyboard::F7, fender::Input::F7},
               {sf::Keyboard::F8, fender::Input::F8},
               {sf::Keyboard::F9, fender::Input::F9},
               {sf::Keyboard::F10, fender::Input::F10},
               {sf::Keyboard::A, fender::Input::A},
               {sf::Keyboard::B, fender::Input::B},
               {sf::Keyboard::C, fender::Input::C},
               {sf::Keyboard::D, fender::Input::D},
               {sf::Keyboard::E, fender::Input::E},
               {sf::Keyboard::F, fender::Input::F},
               {sf::Keyboard::G, fender::Input::G},
               {sf::Keyboard::H, fender::Input::H},
               {sf::Keyboard::I, fender::Input::I},
               {sf::Keyboard::J, fender::Input::J},
               {sf::Keyboard::K, fender::Input::K},
               {sf::Keyboard::L, fender::Input::L},
               {sf::Keyboard::M, fender::Input::M},
               {sf::Keyboard::N, fender::Input::N},
               {sf::Keyboard::O, fender::Input::O},
               {sf::Keyboard::P, fender::Input::P},
               {sf::Keyboard::Q, fender::Input::Q},
               {sf::Keyboard::R, fender::Input::R},
               {sf::Keyboard::S, fender::Input::S},
               {sf::Keyboard::T, fender::Input::T},
               {sf::Keyboard::U, fender::Input::U},
               {sf::Keyboard::V, fender::Input::V},
               {sf::Keyboard::W, fender::Input::W},
               {sf::Keyboard::X, fender::Input::X},
               {sf::Keyboard::Y, fender::Input::Y},
               {sf::Keyboard::Z, fender::Input::Z},
        };

fender::SFMLRender::SFMLRender()
{
    this->initFactory();
    this->_eventSystem.setRole(fender::MediatorRole::Provider);
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
    this->elementFactory["Message"] = [this](fender::Element &src)
    {
        auto *obj = dynamic_cast<fender::Message *>(&src);
        if (obj)
            this->create<types::Message>(*obj);
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
    if (this->currentLayout && this->currentLayout->isVisible())
    {
        for (auto &pair: this->elements)
        {
            auto &elem = *pair.second;
            elem.update();
            if (!elem.src.isVisible())
                continue ;
            elem.drawAll(this->win);
        }
    }
    this->win.display();
}

void fender::SFMLRender::updateChangingKeys()
{
    for (auto &pair: this->inputs)
    {
        if (pair.second == fender::State::GoingUp)
            pair.second = fender::State::Up;
        else if (pair.second == fender::State::GoingDown)
            pair.second = fender::State::Down;
    }
}

inline fender::Command fender::SFMLRender::makeCommand(sf::Event const &event)
{
    try {
        if (event.type == sf::Event::KeyPressed
            && this->inputs[event.key.code] != fender::State::Down) {
            this->inputs[event.key.code] = fender::State::GoingDown;
            return {.key = fenderCodes.at(event.key.code),
                    .state = fender::State::GoingDown};
        } else if (event.type == sf::Event::KeyReleased) {
            this->inputs[event.key.code] = fender::State::GoingUp;
            return {.key = fenderCodes.at(event.key.code),
                    .state = fender::State::GoingUp};
        }
    }
    catch (const std::exception &error)
    {
        LERR("SFML Library does not yet support the required key.");
    }
}

void    fender::SFMLRender::resetKeys()
{
    if (this->_eventSystem.getInputEvents().empty())
        return ;
    for (auto &pair: this->_eventSystem.getInputEvents())
        pair.second->reset();
}

void    fender::SFMLRender::pollEvents()
{
    sf::Event   sfEvent;
//    This function will update already down inputs to update from GoingDown to Down
//    and from GoingUp to Up
    this->resetKeys();
    this->updateChangingKeys();
    while (this->win.pollEvent(sfEvent))
    {
        for (auto &pair: this->_eventSystem.getInputEvents())
        {
            auto &ev = *pair.second;
            if (sfEvent.type == sf::Event::KeyPressed
                || sfEvent.type == sf::Event::KeyReleased)
                ev.matchInput(this->makeCommand(sfEvent));
        }
    }
}

void    fender::SFMLRender::resize(int x, int y)
{
    this->_windowSize.X = x;
    this->_windowSize.Y = y;
    this->win.close();
    this->openWindow();
}

void    fender::SFMLRender::write(int x, int y, std::string const &msg)
{

}

void    fender::SFMLRender::loadCurrentLayout()
{
//    This should be in a LoaderObject for smooth preloading.
    fonts["jedi"].loadFromFile("assets/fonts/jedi.ttf");
    fonts["pixel"].loadFromFile("assets/fonts/pixel.ttf");
    fonts["game"].loadFromFile("assets/fonts/game.ttf");
    fonts["code"].loadFromFile("assets/fonts/code.ttf");
    for (auto const &pair: this->currentLayout->getElements())
    {
        LOUT("SFMLRender:\tLoading " + pair.second->getType() + " " + pair.second->getName());
        this->elementFactory[pair.second->getType()](*pair.second);
    }
}
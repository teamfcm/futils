//
// Created by ganz on 28/07/17.
//

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SFMLRender.hpp"
#include "flog.hpp"

extern "C" fender::SFMLRender* create(std::string const &config)
{
    return new fender::SFMLRender(config);
}

fender::SFMLRender::SFMLRender(std::string const &configFile)
{
    LOUT("SFML Render parsing " + configFile);
}

void    fender::SFMLRender::openWindow()
{
    auto mode = sf::VideoMode::getDesktopMode();
    this->win.create(sf::VideoMode(mode.width / 3, mode.height / 3), "Splashscreen", sf::Style::None);
    this->win.setPosition(sf::Vector2i(mode.width / 2 - win.getSize().x / 2,
                                       mode.height / 2 - win.getSize().y / 2));

    if (!this->texture.loadFromFile("assets/images/fengine.png"))
    {
        LERR("Cannot load file fengine.png");
    }
    this->electricityTexture.loadFromFile("assets/textures/electricity.jpg");
    this->logo.setTexture(this->texture);
    this->texture.setSmooth(true);
    this->back.setFillColor(sf::Color::White);
    this->prog.setTexture(&this->electricityTexture);
    this->back.setPosition(200, 320);
    this->prog.setPosition(200, 320);
    this->logo.setPosition(85, -55);
    this->logo.setScale(sf::Vector2f{0.3, 0.3});

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
    this->win.draw(this->logo);
    this->win.draw(this->back);
    this->win.draw(this->prog);
    // end the current frame
    this->win.display();

    while (this->win.pollEvent(this->events))
    {
        if (this->events.type == sf::Event::Closed)
            this->win.close();
        if (this->events.type == sf::Event::KeyPressed)
        {
            if (this->events.key.code == sf::Keyboard::Escape)
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

    this->prog.setSize(sf::Vector2f(this->progress * 250.0 / 100.0, 10));
    this->progress += 0.1;
    if (this->progress >= 100)
        this->win.close();
}

void    fender::SFMLRender::resize(int x, int y)
{
    this->win.setSize(sf::Vector2u(x, y));
}

void    fender::SFMLRender::write(int x, int y, std::string const &msg)
{

}
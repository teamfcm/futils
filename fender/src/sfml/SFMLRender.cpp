//
// Created by ganz on 28/07/17.
//

#include <iostream>
#include <SFML/Window.hpp>
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

void    fender::SFMLRender::openWindow(int x, int y)
{
    sf::Window  window(sf::VideoMode(800, 600), "Window");
}

void    fender::SFMLRender::closeWindow()
{
    exit(0);
}

void    fender::SFMLRender::refresh()
{

}

void    fender::SFMLRender::write(int x, int y, std::string const &msg)
{

}
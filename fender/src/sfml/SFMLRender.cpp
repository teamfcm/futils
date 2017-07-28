//
// Created by ganz on 28/07/17.
//

#include <iostream>
#include "SFMLRender.hpp"

extern "C" fender::SFMLRender* create(std::string const &config)
{
    return new fender::SFMLRender(config);
}

fender::SFMLRender::SFMLRender(std::string const &configFile)
{
    std::cout << "Parsing " + configFile + " ... " << std::endl;
}

void fender::SFMLRender::hello()
{
    std::cout << "SFML: Hello World !" << std::endl;
}
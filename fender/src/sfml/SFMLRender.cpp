//
// Created by ganz on 28/07/17.
//

#include <iostream>
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

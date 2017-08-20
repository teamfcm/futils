//
// Created by ganz on 17/08/17.
//

#include "Factory.hpp"
#include "AllScenes.hpp"

demo::Factory::Factory()
{
    buildFunctions["intro"] = [this](){
        return std::make_unique<demo::scenes::Splashscreen>(this->env);
    };
}

fender::upScene demo::Factory::build(std::string const &name)
{
    try
    {
        fender::upScene res = this->buildFunctions[name]();
        return res;
    }
    catch (std::exception const &e)
    {
        return nullptr;
    }
}


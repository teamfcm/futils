//
// Created by ganz on 18/09/17.
//

# include "fender.hpp"

void    fender::components::Object2d::setPosition(futils::Vec2d<float> const &pos)
{
    this->position=pos;
}

void    fender::components::Object2d::setSize(futils::Vec2d<float> const &size)
{
    this->size = size;
}

void    fender::components::Object2d::setRPosition(futils::Vec2d<float> const &pos) {
    if (this->parent == nullptr)
    {
        this->position.X = pos.X * fender::IRender::_windowSize.X / 100;
        this->position.Y = pos.Y * fender::IRender::_windowSize.Y / 100;
    }
    else
    {
        this->position.X = pos.X * this->parent->getSize().X / 100;
        this->position.Y = pos.Y * this->parent->getSize().Y / 100;
    }
}

void    fender::components::Object2d::setRSize(futils::Vec2d<float> const &size) {
    if (this->parent == nullptr)
    {
        this->size.X = size.X * fender::IRender::_windowSize.X / 100;
        this->size.Y = size.Y * fender::IRender::_windowSize.Y / 100;
    }
    else
    {
        this->size.X = size.X * this->parent->getSize().X / 100;
        this->size.Y = size.Y * this->parent->getSize().Y / 100;
    }
}
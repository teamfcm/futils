//
// Created by ganz on 18/08/17.
//

# include "fender.hpp"

void fender::IScene::provideRenderer(IRender &renderer)
{
    this->renderer = &renderer;
}
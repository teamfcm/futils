//
// Created by arroganz on 12/17/17.
//

#include "SFMLRenderer.hpp"
#include "Meta.hpp"

fender::systems::SFMLRenderer::SFMLRenderer()
{

}

void fender::systems::SFMLRenderer::init() {
    state = NONE;
    entityManager->addSystem<Meta>();
//    entityManager->addSystem<Box>();
}

void fender::systems::SFMLRenderer::run(float)
{
    // TODO : Encapsulation of finite state machine (no transitions ?)
    switch (state) {
        case NONE: return ;
        case INIT : return init();
        case RENDER : return ;
    }
}
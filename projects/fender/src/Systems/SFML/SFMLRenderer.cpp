//
// Created by arroganz on 12/17/17.
//

#include "SFMLRenderer.hpp"
#include "Window.hpp"

fender::systems::SFMLRenderer::SFMLRenderer()
{

}

void fender::systems::SFMLRenderer::init() {
    state = NONE;
    entityManager->addSystem<SFMLSystems::Window>();
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
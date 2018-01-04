//
// Created by arroganz on 12/17/17.
//

#include "SFMLRenderer.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "Grid.hpp"

fender::systems::SFMLRenderer::SFMLRenderer()
{
    name = "SFML";
}

void fender::systems::SFMLRenderer::init() {
    state = NONE;
    addReaction<events::Shutdown>([this](futils::IMediatorPacket &){
        entityManager->removeSystem(name);
    });
    entityManager->addSystem<SFMLSystems::Window>();
    entityManager->addSystem<SFMLSystems::Input>();
    entityManager->addSystem<SFMLSystems::Camera>();
    entityManager->addSystem<SFMLSystems::Grid>();
}

void fender::systems::SFMLRenderer::run(float)
{
    switch (state) {
        case NONE: return ;
        case INIT : return init();
        case RENDER : return ;
    }
}
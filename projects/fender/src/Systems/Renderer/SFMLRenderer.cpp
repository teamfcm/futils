//
// Created by arroganz on 12/17/17.
//

#include "SFMLRenderer.hpp"

fender::systems::SFMLRenderer::SFMLRenderer()
{

}

void fender::systems::SFMLRenderer::init() {
    phase++;
    addReaction<fender::requests::OpenWindow>([this](futils::IMediatorPacket &pkg) {
        auto &ow = futils::Mediator::rebuild<fender::requests::OpenWindow>(pkg);
        // TODO: Could handle several windows with no problem if i had a map !
        if (this->window == nullptr) {
            auto desktop = sf::VideoMode::getDesktopMode();
            unsigned int w = (unsigned int)(ow.size.w > 1.0 ? ow.size.w : ow.size.w * desktop.width * 100);
            unsigned int h = (unsigned int)(ow.size.h > 1.0 ? ow.size.h : ow.size.h * desktop.height * 100);
            unsigned int x = (unsigned int)(ow.pos.x > 1.0 || ow.pos.x == 0 ? ow.pos.x : ow.pos.x * desktop.width * 100);
            unsigned int y = (unsigned int)(ow.pos.y > 1.0 || ow.pos.y == 0 ? ow.pos.y : ow.pos.y * desktop.height * 100);
            this->window = new sf::RenderWindow(sf::VideoMode(w, h), "Fender");
            this->window->setPosition(sf::Vector2i(x, y));
        }
        phase++;
    });
}

void fender::systems::SFMLRenderer::run(float)
{
    switch (phase) {
        case 0: return init();
        case 1: return ;
    }
}
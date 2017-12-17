//
// Created by arroganz on 12/17/17.
//

#include "SFMLRenderer.hpp"

namespace {
    std::unordered_map<futils::WStyle, sf::Uint32> sfStyle = {
            {futils::WStyle::None, sf::Style::None},
            {futils::WStyle::Titlebar, sf::Style::Titlebar},
            {futils::WStyle::Resize, sf::Style::Resize},
            {futils::WStyle::Close, sf::Style::Close},
            {futils::WStyle::Fullscreen, sf::Style::Fullscreen},
            {futils::WStyle::Default, sf::Style::Default}
    };
}

fender::systems::SFMLRenderer::SFMLRenderer()
{

}

void fender::systems::SFMLRenderer::init() {
    state = NONE;
    addReaction<fender::requests::OpenWindow>([this](futils::IMediatorPacket &pkg) {
        auto &ow = futils::Mediator::rebuild<fender::requests::OpenWindow>(pkg);
        // TODO: Could handle several windows with no problem if i had a map !
        if (this->window == nullptr) {
            auto desktop = sf::VideoMode::getDesktopMode();
            unsigned int w = (unsigned int)(ow.size.w > 1.0 ? ow.size.w : ow.size.w * desktop.width);
            unsigned int h = (unsigned int)(ow.size.h > 1.0 ? ow.size.h : ow.size.h * desktop.height);
            unsigned int x = (unsigned int)(ow.pos.x > 1.0 || ow.pos.x == 0 ? ow.pos.x : ow.pos.x * desktop.width);
            unsigned int y = (unsigned int)(ow.pos.y > 1.0 || ow.pos.y == 0 ? ow.pos.y : ow.pos.y * desktop.height);
            this->window = new sf::RenderWindow(sf::VideoMode(w, h), "Fender", sfStyle[ow.style]);
            this->window->setPosition(sf::Vector2i(x, y));
        }
        state = RENDER;
    });
}

void fender::systems::SFMLRenderer::refreshWindow(float elapsed)
{
    (void)elapsed;

    auto &w = *window;
    if (!w.isOpen())
    {
        // TODO: Should emit an event
        return ;
    }
    w.clear(sf::Color::Black);

    // Event processing
    sf::Event event;
    while (w.pollEvent(event))
    {
        // Request for closing the window
        if (event.type == sf::Event::Closed) {
            // TODO: Should emit an event !
            w.close();
        }
    }

    w.display();
}

void fender::systems::SFMLRenderer::run(float elapsed)
{
    switch (state) {
        case NONE: return ;
        case INIT : return init();
        case RENDER : return refreshWindow(elapsed);
    }
}
//
// Created by clara on 1/8/18.
//

#include "Image.hpp"
#include "Camera.hpp"

namespace fender::systems::SFMLSystems
{
    void Image::renderImage(components::Image const &image, sf::RenderWindow &window){
        auto &absolute = image.getEntity().get<components::AbsoluteTransform>();
        sf::RectangleShape shape;
        sf::Color color;
        color = sf::Color::Black;
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(color);
        shape.setSize(sf::Vector2f(absolute.size.w, absolute.size.h));
        shape.setPosition(absolute.position.x, absolute.position.y);
        window.draw(shape);
    }

    void Image::init() {
        __init();
        addReaction<RenderLayer>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<RenderLayer>(pkg);
            for (auto &obj: packet.objects)
            {
                auto &image = obj->get<components::Image>();
                renderImage(image, *packet.window);
            }
        });
    }

    void Image::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}
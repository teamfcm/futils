//
// Created by arroganz on 1/7/18.
//

#include "Border.hpp"
#include "Camera.hpp"

namespace fender::systems::SFMLSystems
{
    void Border::renderBorder(components::Border const &border, sf::RenderWindow &window)
    {
        auto &absolute = border.getEntity().get<components::AbsoluteTransform>();
        sf::RectangleShape shape;
        sf::Color color;
        color << border.color;
        shape.setOutlineColor(color);
        shape.setSize(sf::Vector2f(absolute.size.w, absolute.size.h));
    }

    void Border::init() {
        addReaction<RenderLayer>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<RenderLayer>(pkg);
            for (auto &obj: packet.objects)
            {
                auto &border = obj->get<components::Border>();
                if (border.visible)
                {
                    renderBorder(border, *packet.window);
                }
            }
        });
    }

    void Border::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}
//
// Created by arroganz on 1/7/18.
//

#include "inputKeys.hpp"
#include "Border.hpp"
#include "Camera.hpp"

namespace fender::systems::SFMLSystems
{
    static std::string lastMessage = "";

    void Border::renderBorder(components::Border const &border, sf::RenderWindow &window)
    {
        auto &absolute = border.getEntity().get<components::AbsoluteTransform>();
        sf::RectangleShape shape;
        sf::Color color;
        color << border.color;
        shape.setFillColor(sf::Color::White);
        shape.setOutlineThickness(border.thickness);
        shape.setOutlineColor(color);
        shape.setSize(sf::Vector2f(absolute.size.w, absolute.size.h));
        shape.setPosition(absolute.position.x, absolute.position.y);
        window.draw(shape);
        lastMessage = "drawing rectangle shape at " + std::to_string(absolute.position.x) + ", " + std::to_string(absolute.position.y)
                + " and size is (" + std::to_string(absolute.size.w) + ", " + std::to_string(absolute.size.h) + ")";
    }

    void Border::init() {
        __init();
        addReaction<futils::Keys>([this](futils::IMediatorPacket &pkg){
            if (this->shouldPrint == false)
                return ;
            auto &key = futils::Mediator::rebuild<futils::Keys >(pkg);
            if (key == futils::Keys::Space)
                std::cout << lastMessage << std::endl;
            this->shouldPrint = false;
        });
        addReaction<RenderLayer>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<RenderLayer>(pkg);
            for (auto &obj: packet.objects)
            {
                auto &border = obj->get<components::Border>();
                if (border.visible) {
                    renderBorder(border, *packet.window);
                }
            }
        });
        phase = Run;
    }

    void Border::run(float) {
        this->shouldPrint = true;
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}
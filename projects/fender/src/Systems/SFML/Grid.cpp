//
// Created by arroganz on 1/4/18.
//

#include "Camera.hpp"
#include "Grid.hpp"

namespace fender::systems::SFMLSystems {
    void Grid::draw(sf::RenderWindow &window, components::Camera &cam)
    {
        if (cam.debugMode == false)
            return;
        sf::Vertex vertical[] = {
                sf::Vertex(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 3 - 10)),
                sf::Vertex(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 3 + 10))
        };
        sf::Vertex horizontal[] = {
                sf::Vertex(sf::Vector2f(window.getSize().x / 3 - 10, window.getSize().y / 3)),
                sf::Vertex(sf::Vector2f(window.getSize().x / 3 + 10, window.getSize().y / 3))
        };
        window.draw(vertical, 2, sf::Lines);
        window.draw(horizontal, 2, sf::Lines);
    }

    void Grid::init()
    {
        __init();
        addReaction<AllLayersRendered>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<AllLayersRendered>(pkg);
            if (!packet.window || !packet.camData)
                return ;
            draw(*packet.window, *packet.camData);
        });
        phase = Run;
    }

    void Grid::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return;
        }
    }
}

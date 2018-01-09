//
// Created by arroganz on 1/4/18.
//

#include <Components/World.hpp>
#include "Camera.hpp"
#include "Grid.hpp"

namespace fender::systems::SFMLSystems {
    void Grid::draw(sf::RenderWindow &window, components::Camera &cam)
    {
        if (cam.debugMode == false)
            return;
        auto worlds = entityManager->get<components::World>();
        if (worlds.empty())
            return ;
        auto world = worlds.front();
        sf::Vertex vertical[] = {
                sf::Vertex(sf::Vector2f(0, 0)),
                sf::Vertex(sf::Vector2f(0, window.getSize().y))
        };
        sf::Vertex horizontal[] = {
                sf::Vertex(sf::Vector2f(0, 0)),
                sf::Vertex(sf::Vector2f(window.getSize().x, 0))
        };
        auto &camPos = cam.getEntity().get<components::Transform>();
        float x{camPos.position.x - (int)camPos.position.x};
        float y{camPos.position.y - (int)camPos.position.y};
        x *= -world->unit;
        y *= -world->unit;
        std::cout << " -> " << x << ", " << y << std::endl;
        while (x < window.getSize().x) {
            vertical[0].position.x = x;
            vertical[1].position.x = x;
            window.draw(vertical, 2, sf::Lines);
            x += world->unit;
        }
        while (y < window.getSize().y)
        {
            horizontal[0].position.y  = y;
            horizontal[1].position.y = y;
            window.draw(horizontal, 2, sf::Lines);
            y += world->unit;
        }
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

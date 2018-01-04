//
// Created by arroganz on 1/4/18.
//

#pragma once

# include "System.hpp"

namespace fender::systems::SFMLSystems
{
    class Grid : public System
    {
        void draw(sf::RenderWindow &, components::Camera &);
        void init();
        enum States
        {
            Init = 0,
            Run
        };

    public:
        Grid() : System("Grid") {}
        void run(float) override;
    };
}
//
// Created by arroganz on 1/7/18.
//


#pragma once

# include <SFML/Graphics.hpp>
# include "System.hpp"
# include "Components/Border.hpp"

namespace fender::systems::SFMLSystems
{
    class Border : public System {
        enum States
        {
            Init = 0,
            Run
        };
        void renderBorder(components::Border const &, sf::RenderWindow &);
        void init();
        bool shouldPrint; // debug only
    public:
        Border(): System("Border") {}
        void run(float) override;
    };
}


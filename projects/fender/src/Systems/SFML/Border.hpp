//
// Created by arroganz on 1/7/18.
//


#pragma once

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
    public:
        void run(float) override;
    };
}


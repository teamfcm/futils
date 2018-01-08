//
// Created by clara on 1/8/18.
//

#pragma once

# include <SFML/Graphics.hpp>
# include "System.hpp"
# include "Components/Image.hpp"

namespace fender::systems::SFMLSystems
{
    class Image : public System {
        enum States
        {
            Init = 0,
            Run
        };
        void renderImage(components::Image const &, sf::RenderWindow &);
        void init();
    public:
        Image(): System("Image") {}
        void run(float) override;
    };
}


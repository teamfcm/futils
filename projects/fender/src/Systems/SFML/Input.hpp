//
// Created by arroganz on 1/1/18.
//

#pragma once

# include "System.hpp"
# include "Components/Input.hpp"

namespace fender::systems::SFMLSystems
{
    class Input : public System
    {
        using Component = components::Input;

        enum States
        {
            Init = 0,
            Run
        };
        int state{Init};

        void process(sf::Event const &event);
        void init();
    public:
        Input() : System("Input") {}
        void run(float) override;
    };
}

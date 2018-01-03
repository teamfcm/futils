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
        using Sequence = futils::InputSequence;

        enum States
        {
            Init = 0,
            Run
        };
        int state{Init};

        void checkInputs();
        void reset();
        void process(sf::Event const &event);
        void init();
    public:
        Input() : System("Input") {}
        void run(float) override;
    };
}

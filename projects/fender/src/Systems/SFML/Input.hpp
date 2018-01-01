//
// Created by arroganz on 1/1/18.
//

#ifndef FENDER_INPUT_HPP
#define FENDER_INPUT_HPP

# include "System.hpp"

namespace fender::systems::SFMLSystems
{
    class Input : public System
    {
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

#endif //FENDER_INPUT_HPP

//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "System.hpp"
# include "Components/Children.hpp"

namespace fender::systems::SFMLSystems
{
    class Children : public System
    {
        enum States
        {
            Init = 0,
            Run
        };

        void init();
    public:
        Children() : System("Children") {}
        void run(float) override;
    };
}
//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "System.hpp"
# include "Components/GameObject.hpp"
# include "Components/Transform.hpp"

namespace fender::systems::SFMLSystems
{
    class Camera : public System
    {
        enum States
        {
            Init = 0,
            Run
        };
        int state{Init};
        void init();
    public:
        Camera() : System("Camera") {}
        void run(float) override;
    };
}
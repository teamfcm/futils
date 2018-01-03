//
// Created by arroganz on 1/3/18.
//

#include "Camera.hpp"

namespace fender::systems::SFMLSystems
{
    void Camera::init()
    {
        __init();
    }

    void Camera::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return;
        }
    }
}
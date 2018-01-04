//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"

namespace fender::entities
{
    class GameObject;
    class Window;
}

namespace fender::components {
    struct Camera : futils::IComponent {
        enum FollowMode
        {
            Instant,
            Slow,
            DistanceFirst
        };

        int viewDistance{10};
        bool debugMode{false};
        bool activated;
        FollowMode mode;
        std::string name;
        entities::Window *window;
        entities::GameObject *target;
    };
}


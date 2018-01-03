//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"

namespace fender::entities
{
    class GameObject;
}

namespace fender::components {
    struct Camera : futils::IComponent {
        enum FollowMode
        {
            Instant,
            Slow,
            DistanceFirst
        };

        std::string name;
        entities::GameObject *target;
        FollowMode mode;
    };
}


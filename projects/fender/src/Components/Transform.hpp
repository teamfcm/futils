//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"
# include "position.hpp"

namespace fender::components {
    struct Transform : futils::IComponent {
        vec3f size;
        Position position;
        float rotation;
    };
}


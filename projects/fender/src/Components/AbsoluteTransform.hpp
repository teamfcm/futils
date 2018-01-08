//
// Created by arroganz on 1/5/18.
//


#pragma once

#include <fender.hpp>

namespace fender::components {
    struct AbsoluteTransform : futils::IComponent {
        vec2i position;
        vec2i size;
    };
}



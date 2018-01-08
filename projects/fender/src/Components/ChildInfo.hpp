//
// Created by arroganz on 1/8/18.
//


#pragma once

# include "fender.hpp"
# include "rendering.hpp"

namespace fender::components {
    struct ChildInfo : futils::IComponent {
        futils::VAlign valign;
        futils::Align align;
        bool isGridRelative{false};
        vec3f offset;
    };
}


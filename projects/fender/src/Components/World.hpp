//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"

namespace fender::components {
    struct World : futils::IComponent {
        int unit{32};
        vec3f size;
        std::string name;
    };
}




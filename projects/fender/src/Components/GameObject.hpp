//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"

namespace fender::components {
    struct GameObject : futils::IComponent {
        bool visible;
    };
}
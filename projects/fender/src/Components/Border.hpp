//
// Created by arroganz on 1/5/18.
//


#pragma once

# include "fender.hpp"
# include "rendering.hpp"

namespace fender::components
{
    struct Border : futils::IComponent
    {
        bool right;
        bool left;
        bool up;
        bool down;
        bool visible;
        futils::Color color;
        int thickness;
    };
}


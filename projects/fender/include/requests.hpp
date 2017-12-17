//
// Created by arroganz on 11/29/17.
//

#ifndef FENDER_REQUESTS_HPP
#define FENDER_REQUESTS_HPP

# include "math.hpp"
# include "mediator.hpp"
# include "ecs.hpp"

namespace fender::requests
{
    struct OpenWindow
    {
        using vec = futils::Vec2<float>;
        vec pos;
        vec size;
        OpenWindow() = default;
        OpenWindow(vec const &pos, vec const &size):
                pos(pos), size(size)
        {

        }
    };
}

#endif //FENDER_REQUESTS_HPP

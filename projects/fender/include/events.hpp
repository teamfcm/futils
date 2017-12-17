//
// Created by arroganz on 11/29/17.
//

#ifndef FENDER_EVENTS_HPP
#define FENDER_EVENTS_HPP

# include "mediator.hpp"
# include "math.hpp"

namespace fender::events {
    struct WindowOpened
    {
        using vec = futils::Vec2<int>;
        vec pos;
        vec size;
    };
}

#endif //FENDER_EVENTS_HPP

//
// Created by arroganz on 12/16/17.
//

#ifndef FENDER_MATH_HPP
#define FENDER_MATH_HPP

namespace futils
{
    template <typename T>
    struct Vec2
    {
        union
        {
            T x;
            T w;
        };
        union
        {
            T y;
            T h;
        };
    };
}

#endif //FENDER_MATH_HPP

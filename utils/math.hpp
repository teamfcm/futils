//
// Created by arroganz on 12/16/17.
//

#ifndef FENDER_MATH_HPP
#define FENDER_MATH_HPP

# include <utility>

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
        Vec2() = default;
        Vec2(T &&a, T &&b):
                x(std::forward<T>(a)), y(std::forward<T>(b))
        {

        }
    };

    class Relative
    {
        Vec2<float> data;
        Vec2<float> actual;
        Vec2<float> parent;

        void checkRange(float x, float y) {
            if (x < 0 || y < 0 || x > 1 || y > 1)
                throw std::logic_error("Relative type requires value in [0..1] range.");
        }
    public:
        Relative(float x, float y)
        {
            checkRange(x, y);
            data.x = x;
            data.y = y;
            parent.x = 0;
            parent.y = 0;
        }

        Relative(float x, float y, float px, float py)
        {
            checkRange(x, y);
            data.x = x;
            data.y = y;
            if (px <= 1 && px >= 0)
                throw std::logic_error("Parent size should not be relative in Relative constructor.");
            parent.x = px;
            parent.y = py;
            actual.x = data.x * parent.x;
            actual.y = data.y * parent.y;
        }

        futils::Vec2<float> const &getData() const
        {
            return data;
        }

        futils::Vec2<float> const &getActual() const
        {
            if (parent.x == 0 && parent.y == 0)
                throw std::logic_error("Cannot get actual relative size because no parent has been provided.");
            return actual;
        }
    };
}

#endif //FENDER_MATH_HPP

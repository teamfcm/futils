//
// Created by arroganz on 12/16/17.
//

#ifndef FENDER_MATH_HPP
#define FENDER_MATH_HPP

# include <utility>
# include "range.hpp"

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
        Vec2()
        {

        }
        Vec2(Vec2 const &other):
                x(other.x), y(other.y)
        {

        }
        Vec2(T &&a, T &&b):
                x(std::forward<T>(a)), y(std::forward<T>(b))
        {

        }
    };

    template <typename T>
    struct Vec3
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
        T z;

        Vec3()
        {

        }
        Vec3(Vec3 const &other):
                x(other.x), y(other.y), z(other.z)
        {

        }
        Vec3(T &&a, T &&b, T &&c):
                x(std::forward<T>(a)), y(std::forward<T>(b)), z(std::forward<T>(c))
        {

        }
    };
    
    class Pct
    {
        float value;

        void checkRange(float &val) {
            static futils::FloatingRange<float> frac(0, 100);
            if (!frac.contains(val))
                throw std::logic_error("Pct type requires relative values (0..100)");
        }
    public:
        Pct(Pct const &other)
        {
            value = other.get();
        }
        Pct(float x):
                value(0)
        {
            set(x);
        }

        void set(float val)
        {
            checkRange(val);
            value = val;
        }

        float get() const
        {
            return value;
        }

        float operator * (float const &other) const
        {
            return value / 100 * other;
        }

        unsigned int operator * (unsigned int &other) const
        {
            return (unsigned int)((value / 100) * other);
        }

        Pct operator + (Pct const &other)
        {
            return Pct(value + other.get());
        }

        Pct &operator += (Pct const &other)
        {
            value += other.get();
            return *this;
        }

        operator unsigned int () const
        {
            return (unsigned int)value;
        }

        operator float () const
        {
            return value;
        }
    };
}

#endif //FENDER_MATH_HPP

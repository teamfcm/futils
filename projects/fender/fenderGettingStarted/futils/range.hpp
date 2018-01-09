//
// Created by arroganz on 12/19/17.
//

#ifndef FENDER_RANGE_HPP
#define FENDER_RANGE_HPP

# include <random>

namespace futils
{
    template    <typename T>
    class       IntegralRange
    {
        T       minimum;
        T       maximum;
    public:
        IntegralRange(T min, T max):
                minimum(min), maximum(max)
        {
            static_assert(std::is_integral<T>::value,
                          "Integral Range requires integral values");
        }

        void    setMinimum(T min){this->minimum = min;}
        void    setMaximum(T max){this->maximum = max;}
        T       getMaximum() const {return this->maximum;}
        T       getMinimum() const {return this->minimum;}
        bool    contains(T value) const {return value >= minimum && value <= maximum;}
        T       getRandom() const
        {
            std::random_device  rd;
            std::mt19937        rng(rd());
            std::uniform_int_distribution<T> gen(this->minimum, this->maximum);
            return gen(rng);
        }
    };

    template    <typename T>
    class       FloatingRange
    {
        T       minimum;
        T       maximum;
    public:
        FloatingRange(T min, T max):
                minimum(min), maximum(max)
        {
            static_assert(std::is_floating_point<T>::value,
                          "Floating Range requires floating values");
            if (max <= min)
                throw std::runtime_error("Cannot create negative range with "
                                         + std::to_string(min) + " "
                                         + std::to_string(max));
        }

        void    setMinimum(T min){this->minimum = min;}
        void    setMaximum(T max){this->maximum = max;}
        T       getMaximum() const {return this->maximum;}
        T       getMinimum() const {return this->minimum;}
        bool    contains(T value) const {return value >= minimum && value <= maximum;}
        T       getRandom() const
        {
            std::random_device  rd;
            std::mt19937        rng(rd());
            std::uniform_real_distribution<T> gen(this->minimum, this->maximum);
            return gen(rng);
        }
    };
}

#endif //FENDER_RANGE_HPP

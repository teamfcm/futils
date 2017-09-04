//
// Created by ganz on 17/08/17.
//

#ifndef DEMO_FUTILS_HPP
#define DEMO_FUTILS_HPP

# include <mutex>
# include <chrono>
# include <functional>
# include <random>

namespace futils
{
    using voidFunc = std::function<void(void)>;
    using voidStringFunc = std::function<void(std::string const &)>;
    template        <typename __Key, typename __ValueType>
    using umap = std::unordered_map<__Key, __ValueType>;

    class   ScopeLock
    {
        std::mutex  &owned;
    public:
        ScopeLock(std::mutex &mutex): owned(mutex)
        {
            owned.lock();
        }
        ~ScopeLock() { owned.unlock(); }
    };

    template    <typename T>
    struct      Vec2d
    {
        T       X;
        T       Y;
    };

    template    <typename T>
    struct      Vec3d
    {
        T       X;
        T       Y;
        T       Z;
    };
    
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
    
    
    namespace string
    {
        inline bool     isNumber(std::string const &str)
        {
            return str.find_first_not_of("0123456789") == std::string::npos;
        }
    }
}

#endif //DEMO_FUTILS_HPP

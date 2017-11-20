//
// Created by ganz on 17/08/17.
//

#ifndef DEMO_FUTILS_HPP
#define DEMO_FUTILS_HPP

# include <mutex>
# include <chrono>
# include <functional>
# include <random>
# include <unordered_map>

namespace futils
{
    using voidFunc = std::function<void(void)>;
    using voidStringFunc = std::function<void(std::string const &)>;
    template        <typename __Key, typename __ValueType>
    using umap = std::unordered_map<__Key, __ValueType>;
    
    class   UID
    {
        UID() = default;
    public:
        int _current{0};
        static int get()
        {
            static UID *singleton = new UID();
            return singleton->_current++;
        }
    };
    
    class   Clock
    {
        using clock = std::chrono::system_clock;
        
        clock::time_point startPoint{clock::now()};
        clock::time_point endPoint{clock::now()};
        float             buffer{0.0};
        float             elapsed{0.0};
    public:
        Clock() = default;
        
        float       loop()
        {
            elapsed = std::chrono::duration<float>(this->endPoint - this->startPoint).count();
            buffer += elapsed;
            return this->elapsed;
        }
        
        float       bufferedElapsedTime()
        {
            return this->buffer;
        }
        
        void        resetBuffer()
        {
            this->buffer = 0.0;
        }
        
        void        start()
        {
            this->startPoint = std::chrono::system_clock::now();
        }
        
        void        end()
        {
            this->endPoint = std::chrono::system_clock::now();
        }
    };
    
    class   Choice
    {
        std::string label{"Undefined"};
    public:
        Choice() = default;
        Choice(std::string const &label): label(label) {}
        std::string const &getLabel() const {return this->label;}
        voidFunc    action{[](){}};
    };
    
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
    struct      Rect
    {
        T       X{0};
        T       Y{0};
        T       EndX{0};
        T       EndY{0};
    public:
        Rect() = default;
        Rect(futils::Vec2d<T> const &pos, futils::Vec2d<T> const &size):
                X(pos.X), Y(pos.Y), EndX(X + size.X), EndY(Y + size.Y) {}
        Rect(Rect<T> const &ref):
                X(ref.X), Y(ref.Y), EndX(ref.EndX), EndY(ref.EndY) {}
        
        template    <typename OtherType>
        bool        contains(futils::Vec2d<OtherType> const &pos) const {
            static_assert(std::is_arithmetic<OtherType>::value,
                          "Rect.contains failed because OtherType is not arithmetic.");
            return (pos.X >= X && pos.X <= EndX
                    && pos.Y >= Y && pos.Y <= EndY);
        }
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
        
        inline std::vector<std::string>    split(std::string const &parent, char delim)
        {
            std::vector<std::string>    result;
            std::stringstream           ss;
            ss.str(parent);
            std::string elem;
            while (std::getline(ss, elem, delim))
            {
                if (elem != "")
                    result.push_back(elem);
            }
            return result;
        }
    }
    
    namespace collision
    {
        template    <typename T = int>
        bool        rectContains(futils::Rect<T> &rect, futils::Vec2d<T> const &pos)
        {
            return rect.contains(pos);
        }
    }
}

#endif //DEMO_FUTILS_HPP

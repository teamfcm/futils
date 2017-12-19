//
// Created by ganz on 17/08/17.
//

#ifndef DEMO_FUTILS_HPP
#define DEMO_FUTILS_HPP

# include <sstream>
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

    class   Choice
    {
        std::string label{"Undefined"};
    public:
        Choice() = default;
        Choice(std::string const &label): label(label) {}
        std::string const &getLabel() const {return this->label;}
        voidFunc    action{[](){}};
    };

    inline void NotImplemented(std::string const &name)
    {
        throw std::logic_error(name + " is not implemented yet");
    }

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

//
// Created by ganz on 17/08/17.
//

#ifndef DEMO_FUTILS_HPP
#define DEMO_FUTILS_HPP

# include <mutex>
# include <functional>

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

    namespace string
    {
        inline bool     isNumber(std::string const &str)
        {
            return str.find_first_not_of("0123456789") == std::string::npos;
        }
    }
}

#endif //DEMO_FUTILS_HPP

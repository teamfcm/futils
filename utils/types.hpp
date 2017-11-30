//
// Created by arroganz on 11/23/17.
//

#ifndef FUTILS_TYPES_H
#define FUTILS_TYPES_H

# include <typeindex>
# include <functional>
#if linux
# include <cxxabi.h>
#elif __WIN32

#endif
# include <memory>
# include "fstring.hpp"

namespace futils
{
    /*
     *  This file defines type aliases
     *  For more information, check the documentation on
     *  https://github.com/teamfcm/futils
     */

    /*
     * Functional wrappers.
     */
    template <typename ...Args>
    using Predicate = std::function<bool(Args...)>;
    template <typename ...Args>
    using Task = std::function<void(Args...)>;
    using Action = std::function<void(void)>;

    template <typename T>
    using UP = std::unique_ptr<T>;
    template <typename T>
    using SP = std::shared_ptr<T>;

    // Similar to putils::pmeta::type_index ;)
    using type_index = size_t;
    template<typename T>
    struct type
    {
        using wrapped = T;
        static const type_index index;
    };

    template<typename T>
    const futils::type_index futils::type<T>::index = std::hash<std::type_index>()(std::type_index(typeid(T)));

    template <typename T>
    std::string demangle()
    {
        std::string full{typeid(T).name()};
#ifdef linux
        full = abi::__cxa_demangle(full.c_str(), 0, 0, nullptr);
        full = futils::string::split(full, ':').back();
        return full;
#elif _WIN32
        // TODO: Test on windows
        return full;
#endif
    }
}

#endif //FUTILS_TYPES_H

//
// Created by arroganz on 11/23/17.
//

#ifndef FUTILS_TYPES_H
#define FUTILS_TYPES_H

# include <cxxabi.h>
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

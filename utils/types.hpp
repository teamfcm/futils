//
// Created by arroganz on 11/23/17.
//

#ifndef FUTILS_TYPES_H
#define FUTILS_TYPES_H

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
}

#endif //FUTILS_TYPES_H

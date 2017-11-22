//
// Created by arroganz on 11/21/17.
//

#ifndef FUTILS_SCOPELOCK_H
#define FUTILS_SCOPELOCK_H

#include <mutex>

namespace futils
{
    // Deprecated - prefer c++17 std::scoped_lock from <mutex>
    class   ScopeLock
    {
        std::mutex  &owned;
    public:
        ScopeLock(std::mutex &mutex): owned(mutex) { owned.lock(); }
        ~ScopeLock() { owned.unlock(); }
    };
}

#endif //FUTILS_SCOPELOCK_H

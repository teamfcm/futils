//
// Created by ganz on 17/08/17.
//

#ifndef DEMO_FUTILS_HPP
#define DEMO_FUTILS_HPP

# include <mutex>

namespace futils
{
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
}

#endif //DEMO_FUTILS_HPP

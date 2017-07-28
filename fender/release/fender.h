#ifndef FENDER_LIBRARY_H
#define FENDER_LIBRARY_H

namespace fender
{
    class IRender
    {
    public:
        virtual ~IRender() = default;

        virtual void        hello() = 0;
    };
}

#endif
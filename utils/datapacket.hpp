//
// Created by arroganz on 11/28/17.
//

#ifndef DEMO_DATAPACKET_HPP
#define DEMO_DATAPACKET_HPP

# include "types.hpp"

namespace futils
{
    struct IMediatorPacket
    {
        virtual ~IMediatorPacket() = default;
        IMediatorPacket(futils::type_index t): type(t) {}

        futils::type_index type;
    };

    template <typename T>
    struct AMediatorPacket : public IMediatorPacket
    {
        AMediatorPacket() : IMediatorPacket(futils::type<T>::index) {}
    };
}

#endif //DEMO_DATAPACKET_HPP

//
// Created by arroganz on 11/28/17.
//

#ifndef DEMO_DATAPACKET_HPP
#define DEMO_DATAPACKET_HPP

# include "types.hpp"
# include "customTraits.hpp"

namespace futils
{
    struct IMediatorPacket
    {
        virtual ~IMediatorPacket() = default;
        IMediatorPacket(futils::type_index t): type(t) {}

        futils::type_index type;
    };

    template <typename T>
    class AMediatorPacket : public IMediatorPacket
    {
        T const &load;
    public:
        AMediatorPacket(T const &data):
                IMediatorPacket(futils::type<T>::index),
                load(data)
        {

        }

//        template <typename U = T,
//        typename std::enable_if<futils::_has_no_fields_<U>::value, AMediatorPacket>::type>
//        AMediatorPacket():
//                IMediatorPacket(futils::type<U>::index)
//        {
//
//        }

        const T &get() const {
            return load;
        }
    };
}

#endif //DEMO_DATAPACKET_HPP

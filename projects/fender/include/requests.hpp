//
// Created by arroganz on 11/29/17.
//

#ifndef FENDER_REQUESTS_HPP
#define FENDER_REQUESTS_HPP

# include "mediator.hpp"

namespace fender::requests
{
    struct GetRenderer : futils::AMediatorPacket<GetRenderer> {};
    struct OpenWindow : futils::AMediatorPacket<OpenWindow>
    {
        std::string name;
        int width;
        int height;
    };
}

#endif //FENDER_REQUESTS_HPP

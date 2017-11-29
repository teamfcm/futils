//
// Created by arroganz on 11/29/17.
//

#ifndef FENDER_EVENTS_HPP
#define FENDER_EVENTS_HPP

# include "mediator.hpp"

// Forward Declarations
namespace fender
{
    class IRender;
}

namespace fender::events {

    struct RendererAccess : futils::AMediatorPacket<RendererAccess>
    {
        IRender *renderer{nullptr};
    };

    struct WindowOpened : futils::AMediatorPacket<WindowOpened>
    {
        std::string name;
        int width;
        int height;
    };
}

#endif //FENDER_EVENTS_HPP

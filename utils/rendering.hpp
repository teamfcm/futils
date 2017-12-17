//
// Created by arroganz on 12/17/17.
//

#ifndef FENDER_RENDERING_HPP
#define FENDER_RENDERING_HPP

// This header file is a list of abstract types representing various rendering elements

namespace futils
{
    enum class WStyle : uint32_t
    {
        None       = 0,
        Titlebar   = 1 << 0,
        Resize     = 1 << 1,
        Close      = 1 << 2,
        Fullscreen = 1 << 3,
        Default = Titlebar | Resize | Close
    };
}

#endif //FENDER_RENDERING_HPP

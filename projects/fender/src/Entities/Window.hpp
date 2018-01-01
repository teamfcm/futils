//
// Created by arroganz on 1/1/18.
//

#ifndef FENDER_WINDOW_HPP
#define FENDER_WINDOW_HPP

# include "fender.hpp"
# include "Components/Window.hpp"

namespace fender::entities
{
    class Window : public futils::IEntity
    {
    public:
        Window() {
            attach<components::Window>();
        }
    };
}

#endif //FENDER_WINDOW_HPP

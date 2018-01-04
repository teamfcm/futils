//
// Created by arroganz on 1/1/18.
//

#pragma once

# include "fender.hpp"
# include "Components/Window.hpp"

namespace fender::entities
{
    class Window : public futils::IEntity
    {
    public:
        Window() {
            std::cout << futils::type<futils::ComponentAttached<components::Window>>::index << " is the type of window attach compo" << std::endl;
            attach<components::Window>();
        }
        ~Window()
        {
            detach<components::Window>();
        }
    };
}

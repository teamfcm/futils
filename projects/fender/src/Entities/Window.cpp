//
// Created by arroganz on 12/18/17.
//

#include "Window.hpp"

fender::entities::Window::Window(std::string const &name,
                                 futils::Relative pos, futils::Relative size,
                                 futils::WStyle style)
{
    attach<fender::components::Meta>(name, style);
    attach<fender::components::Box>(pos, size);
}

fender::entities::Window::Window(std::string const &name,
                                 futils::Vec2<int> pos, futils::Vec2<int> size,
                                 futils::WStyle style)
{
    attach<fender::components::Meta>(name, style);
    attach<fender::components::Box>(pos, size);
}
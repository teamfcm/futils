//
// Created by arroganz on 12/18/17.
//

#ifndef FENDER_WINDOW_HPP
#define FENDER_WINDOW_HPP

# include "rendering.hpp"
# include "ecs.hpp"
# include "math.hpp"

namespace fender::entities
{
    class Window : public futils::IEntity {
    public:
        Window(std::string const &name,
               futils::Vec2<int> pos, futils::Vec2<int> size,
               futils::WStyle = futils::WStyle::Default);
        Window(std::string const &name,
               futils::Relative pos, futils::Relative size,
               futils::WStyle = futils::WStyle::Default);
    };
}

#endif //FENDER_WINDOW_HPP

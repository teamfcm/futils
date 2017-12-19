//
// Created by arroganz on 12/18/17.
//

#ifndef FENDER_WINDOW_HPP
#define FENDER_WINDOW_HPP

# include "rendering.hpp"
# include "ecs.hpp"
# include "math.hpp"

# include "../Components/Meta.hpp"
# include "../Components/Box.hpp"

namespace fender::entities
{
    class Window : public futils::IEntity {
    public:
        Window(std::string const &name,
               futils::Vec2<int> pos, futils::Vec2<int> size,
               futils::WStyle = futils::WStyle::Default);
        Window(std::string const &name,
               futils::Vec2<futils::Pct> pos, futils::Vec2<futils::Pct> size,
               futils::WStyle = futils::WStyle::Default);
    };
}

#endif //FENDER_WINDOW_HPP

//
// Created by arroganz on 12/18/17.
//

#ifndef FENDER_BOX_HPP
#define FENDER_BOX_HPP

# include "ecs.hpp"
# include "math.hpp"

namespace fender::components {
    class Box : public futils::IComponent {
    public:
        Box(futils::Relative const &, futils::Relative const &) {}
        Box(futils::Vec2<int> const &, futils::Vec2<int> const &) {}
    };
}


#endif //FENDER_BOX_HPP

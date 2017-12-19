//
// Created by arroganz on 12/18/17.
//

#ifndef FENDER_BOX_HPP
#define FENDER_BOX_HPP

# include "ecs.hpp"
# include "math.hpp"

namespace fender::components {
    class Box : public futils::IComponent {
        futils::Vec2<int> pos;
        futils::Vec2<int> size;
    public:
        Box(futils::Relative const &pos, futils::Relative const &size) {
            auto &actualPos = pos.getActual();
            this->pos.x = actualPos.x;
            this->pos.y = actualPos.y;
            auto &actualSize = size.getActual();
            this->size.w = actualSize.w;
            this->size.h = actualSize.h;
        }
        Box(futils::Vec2<int> const &pos, futils::Vec2<int> const &size): pos(pos), size(size) {}

        void print(std::ostream &os) const {
            os << "[x:" << pos.x << ",y:" << pos.y << "|w:" << size.w << ",h:" << size.h << "]" << std::endl;
        }
    };

    std::ostream &operator << (std::ostream &os, Box const &b)
    {
        b.print(os);
        return os;
    }
}


#endif //FENDER_BOX_HPP

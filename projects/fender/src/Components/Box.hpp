//
// Created by arroganz on 12/18/17.
//

#ifndef FENDER_BOX_HPP
#define FENDER_BOX_HPP

# include "ecs.hpp"
# include "math.hpp"

namespace fender::components {
    class Box : public futils::IComponent {
        bool relative{false};
        futils::Vec2<futils::Pct> rpos;
        futils::Vec2<futils::Pct> rsize;
        futils::Vec2<float> pos;
        futils::Vec2<float> size;
    public:
        Box(futils::Vec2<futils::Pct> const &pos, futils::Vec2<futils::Pct> const &size) {
            rpos.x = pos.x;
            rpos.y = pos.y;
            rsize.w = size.w;
            rsize.h = size.h;
            relative = true;
        }
        Box(futils::Vec2<int> const &pos, futils::Vec2<int> const &size)
        {
            this->pos.x = pos.x;
            this->pos.y = pos.y;
            this->size.w = size.w;
            this->size.h = size.h;
        }

        futils::Vec2<float> const &getPos() const {
            return pos;
        }

        futils::Vec2<float> const &getSize() const {
            return size;
        }

        futils::Vec2<futils::Pct> const &getRPos() const {
            return rpos;
        }

        futils::Vec2<futils::Pct> const &getRSize() const {
            return rsize;
        }

        bool isRelative()
        {
            return relative;
        }

        void print(std::ostream &os) const {
            os << "[x:" << pos.x << ",y:" << pos.y << "|w:" << size.w << ",h:" << size.h << "]" << std::endl;
        }
    };

    inline std::ostream &operator << (std::ostream &os, Box const &b)
    {
        b.print(os);
        return os;
    }
}


#endif //FENDER_BOX_HPP

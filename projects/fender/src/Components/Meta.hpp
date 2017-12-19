//
// Created by arroganz on 12/18/17.
//

#ifndef FENDER_META_HPP
#define FENDER_META_HPP

# include "ecs.hpp"
# include "rendering.hpp"

namespace fender::components {
    class Meta : public futils::IComponent {
        std::string name;
        futils::WStyle style;
    public:
        Meta(std::string const &, futils::WStyle) {}
        void print(std::ostream &os) const
        {
            os << "Meta Object [" << name << "] : " << style << std::endl;
        }
    };

    std::ostream &operator << (std::ostream &os, Meta const &m)
    {
        m.print(os);
        return os;
    }
}

#endif //FENDER_META_HPP

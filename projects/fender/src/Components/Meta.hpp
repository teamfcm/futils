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
        futils::Color bgColor{futils::Granite};
    public:
        Meta(std::string const &name, futils::WStyle style):
                name(name), style(style)
        {

        }

        std::string const &getName() const noexcept
        {
            return name;
        }

        futils::WStyle getStyle() const noexcept
        {
            return style;
        }

        futils::Color getColor() const noexcept
        {
            return bgColor;
        }

        void print(std::ostream &os) const
        {
            os << "Meta Object [" << name << "] : " << style << std::endl;
        }

        void setColor(futils::Color color) {
            bgColor = color;
        }
    };

    inline std::ostream &operator << (std::ostream &os, Meta const &m)
    {
        m.print(os);
        return os;
    }
}

#endif //FENDER_META_HPP

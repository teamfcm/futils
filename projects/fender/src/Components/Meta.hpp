//
// Created by arroganz on 12/18/17.
//

#ifndef FENDER_META_HPP
#define FENDER_META_HPP

# include "ecs.hpp"
# include "rendering.hpp"

namespace fender::components {
    class Meta : public futils::IComponent {
    public:
        Meta(std::string const &, futils::WStyle) {}
    };
}

#endif //FENDER_META_HPP

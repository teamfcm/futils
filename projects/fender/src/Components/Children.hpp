//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"
# include "rendering.hpp"

namespace fender::entities
{
    class GameObject;
}

namespace fender::components {
    struct Children : futils::IComponent {
        bool reversed;
        float padding;
        futils::Align align;
        futils::VAlign valign;
        futils::Ordering order;
        std::vector<entities::GameObject *> content;
    };
}


//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"

namespace fender::entities
{
    class GameObject;
}

namespace fender::components {
    struct Children : futils::IComponent {
        std::vector<entities::GameObject *> content;
    };
}


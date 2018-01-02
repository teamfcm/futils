//
// Created by arroganz on 1/2/18.
//

#pragma once

# include "fender.hpp"
# include "inputKeys.hpp"

namespace fender::components {
    struct Input : futils::IComponent {
        bool activated{false};
        std::string name;
        std::unordered_map<futils::InputSequence, std::function<void()>> map;
    };
}

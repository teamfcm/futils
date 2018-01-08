//
// Created by clara on 1/3/18.
//

#pragma once

# include "fender.hpp"

namespace fender::components {
    struct Image : futils::IComponent {
        std::string file;
    };
}
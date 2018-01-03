//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"
# include "Components/World.hpp"

namespace fender::entities {
    class World : futils::IEntity {
    public:
        World() {
            attach<components::World>();
        }
        ~World() {
            detach<components::World>();
        }
    };
}


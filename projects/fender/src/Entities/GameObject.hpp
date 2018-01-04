//
// Created by arroganz on 1/3/18.
//


#pragma once

# include "fender.hpp"
# include "Components/GameObject.hpp"
# include "Components/Transform.hpp"

namespace fender::entities {
    class GameObject : public futils::IEntity {
    public:
        GameObject() {
            attach<components::GameObject>();
            auto &transform = attach<components::Transform>();
            transform.position.z = 1;

        }
        ~GameObject() {
            detach<components::GameObject>();
            detach<components::Transform>();
        }
    };
}


//
// Created by arroganz on 1/3/18.
//


#pragma once

#include <Components/AbsoluteTransform.hpp>
#include <Components/Border.hpp>
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
            attach<components::AbsoluteTransform>();
            auto &border = attach<components::Border>();
            border.color = futils::Indianred;
            border.thickness = 2;
            border.visible = true;
        }
        ~GameObject() {
            detach<components::GameObject>();
            detach<components::Transform>();
            detach<components::AbsoluteTransform>();
        }
    };
}


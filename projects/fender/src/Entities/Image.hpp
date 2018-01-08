//
// Created by clara on 1/3/18.
//


#pragma once

#include <Components/AbsoluteTransform.hpp>
# include "fender.hpp"
# include "Components/GameObject.hpp"
# include "Components/Transform.hpp"
# include "Components/Image.hpp"

namespace fender::entities {
    class Image : public futils::IEntity {
    public:
        Image() {
            attach<components::GameObject>();
            auto &transform = attach<components::Transform>();
            transform.position.z = 1;
            attach<components::AbsoluteTransform>();
            auto &image = attach<components::Image>();
            image.file = "lala.png";
        }
        ~Image() {
            detach<components::GameObject>();
            detach<components::Transform>();
            detach<components::AbsoluteTransform>();
        }
    };
}
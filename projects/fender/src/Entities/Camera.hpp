//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"
# include "GameObject.hpp"
# include "Components/Camera.hpp"
# include "Components/Children.hpp"

namespace fender::entities {
    class Camera : public GameObject {
    public:
        Camera() {
            auto &transform = get<components::Transform>();
            transform.position.z = 10;
            attach<components::Camera>();
            attach<components::Children>();
        }
        ~Camera() {
            detach<components::Camera>();
            detach<components::Children>();
        }
    };
}



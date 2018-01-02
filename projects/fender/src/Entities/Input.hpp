//
// Created by arroganz on 1/2/18.
//

#pragma once

# include "fender.hpp"
# include "Components/Input.hpp"

namespace fender::entities
{
    class Input : public futils::IEntity
    {
    public:
        Input() {
            attach<fender::components::Input>();
        }
        ~Input()
        {
            detach<fender::components::Input>();
        }
    };
}

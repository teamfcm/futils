//
// Created by arroganz on 1/3/18.
//

#include "Children.hpp"

namespace fender::systems::SFMLSystems
{
    void Children::run(float) {
        switch (phase)
        {
            case Init : return init();
            case Run : return ;
        }
    }

    void Children::init() {
        __init();
    }
}
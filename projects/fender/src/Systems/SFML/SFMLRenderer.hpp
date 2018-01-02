//
// Created by arroganz on 12/17/17.
//

#pragma once

// TODO: Change CMAKELISTS.TXT to make this compile :)
# include <SFML/Graphics.hpp>

# include "ecs.hpp"
# include "events.hpp"
# include "rendering.hpp"
# include "System.hpp"

namespace fender::systems {
    class SFMLRenderer : public futils::ISystem {
         enum State
        {
            NONE = -1,
            INIT = 0,
            RENDER
        };
        State state{INIT};

        void requireEvents();
        void init();
    public:
        SFMLRenderer();
        void run(float) final;
    };
}

inline sf::Color &operator << (sf::Color &lhs, futils::Color const &rhs)
{
    //TODO: Big endian//litte endian ??
    lhs.r = rhs.rgba[2];
    lhs.g = rhs.rgba[1];
    lhs.b = rhs.rgba[0];
    lhs.a = rhs.rgba[3];
    return lhs;
}

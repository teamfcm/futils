//
// Created by arroganz on 12/17/17.
//

#ifndef FENDER_RENDERER_HPP
#define FENDER_RENDERER_HPP

# include <SFML/Graphics.hpp>

# include "ecs.hpp"
# include "events.hpp"
# include "requests.hpp"

namespace fender::systems {
    class SFMLRenderer : public futils::ISystem {
        sf::RenderWindow *window{nullptr};
        int phase{0};
        void init();
    public:
        SFMLRenderer();
        void run(float) final;
    };
}


#endif //FENDER_RENDERER_HPP

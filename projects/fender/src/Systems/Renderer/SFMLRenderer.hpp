//
// Created by arroganz on 12/17/17.
//

#ifndef FENDER_RENDERER_HPP
#define FENDER_RENDERER_HPP

# include <SFML/Graphics.hpp>

# include "ecs.hpp"
# include "events.hpp"
# include "requests.hpp"
# include "rendering.hpp"

namespace fender::systems {
    class SFMLRenderer : public futils::ISystem {
        // TODO: Encapsulate Window abstraction
        sf::Color clearColor;

        // TODO: Some encapsulation might be nice!
        enum State
        {
            NONE = -1,
            INIT = 0,
            RENDER
        };
        State state{INIT};

        sf::RenderWindow *window{nullptr};
        void init();
        void refreshWindow(float);
    public:
        SFMLRenderer();
        void run(float) final;
    };
}


#endif //FENDER_RENDERER_HPP

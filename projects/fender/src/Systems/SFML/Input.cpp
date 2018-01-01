//
// Created by arroganz on 1/1/18.
//

#include <SFML/Window/Event.hpp>
#include "Input.hpp"
#include "inputKeys.hpp"

namespace fender::systems::SFMLSystems
{
    void Input::init()
    {
        __init();
        addReaction<sf::Event>([this](futils::IMediatorPacket &pkg){
            auto &event = futils::Mediator::rebuild<sf::Event>(pkg);
            process(event);
        });
    }

    void Input::process(sf::Event const &event)
    {
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Key::Escape)
                events->send<futils::Input>(futils::Input::Escape);
        }
        state = Run;
    }

    void Input::run(float) {
        switch (state)
        {
            case Init : return init();
            // Run could be something like update all inputs ?
            case Run : return ;
        }
    }
}
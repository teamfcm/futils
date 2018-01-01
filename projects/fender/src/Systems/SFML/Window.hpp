//
// Created by arroganz on 1/1/18.
//

#ifndef FENDER_WINDOW_HPP
#define FENDER_WINDOW_HPP

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include "System.hpp"
# include "Components/Window.hpp"

namespace fender::systems::SFMLSystems
{
    class Window : public System
    {
        using Component = components::Window;
        using WindowContainer = std::unordered_map<std::string, components::Window *>;
        enum States
        {
            INIT = 0,
            RUN
        };

        WindowContainer _windows;

        void open(Component &);
        void close(Component &);
        void requireEvents();
        void onWindowDestroyed(Component &);
        void onNewWindow(Component &);
        void init();
    public:
        void run(float) override;
    };
}

#endif //FENDER_WINDOW_HPP

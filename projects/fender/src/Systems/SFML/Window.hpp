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

        struct RealWindow
        {
            sf::RenderWindow *win{nullptr};
            Component *data{nullptr};
        };
        using WindowContainer = std::unordered_map<std::string, RealWindow>;
        enum States
        {
            INIT = 0,
            RUN
        };

        WindowContainer _windows;

        void pollEvents(RealWindow &real);
        void open(RealWindow &);
        void close(RealWindow &);
        void requireEvents();
        void onWindowDestroyed(Component &);
        void onNewWindow(Component &);
        void init();
    public:
        Window(): System("Window") {}
        void run(float) override;
    };
}

#endif //FENDER_WINDOW_HPP

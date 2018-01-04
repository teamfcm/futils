//
// Created by arroganz on 1/3/18.
//

#pragma once

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include "System.hpp"
# include "Entities/Window.hpp"
# include "Entities/GameObject.hpp"
# include "Components/Camera.hpp"

namespace fender::systems::SFMLSystems
{
    class Camera : public System
    {
        enum States
        {
            Init = 0,
            Run
        };
        int state{Init};

        std::unordered_map<futils::IEntity *, sf::RenderWindow *> camToWindow;
        std::unordered_multimap<int, futils::IEntity *> layout;
        void renderWindow(futils::IEntity &cam);

        void drawCamCrosshair(components::Camera &, sf::RenderWindow *);
        void sortGameObjects();
        void renderEachCam();
        void init();
    public:
        Camera() : System("Camera") {}
        void run(float) override;
    };

    struct RenderLayer
    {
        int layer;
        sf::RenderWindow *window;
        components::Camera *camData;
        std::vector<futils::IEntity *> objects;
    };

    struct AllLayersRendered
    {
        sf::RenderWindow *window;
        components::Camera *camData;
    };
}
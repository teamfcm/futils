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
# include "Components/World.hpp"

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
        void renderCam(futils::IEntity &, components::Camera &, components::World &);
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

inline sf::Color &operator << (sf::Color &lhs, futils::Color const &rhs)
{
    //TODO: Big endian//litte endian ??
    lhs.r = rhs.rgba[2];
    lhs.g = rhs.rgba[1];
    lhs.b = rhs.rgba[0];
    lhs.a = rhs.rgba[3];
    return lhs;
}
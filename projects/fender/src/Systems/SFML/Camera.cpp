//
// Created by arroganz on 1/3/18.
//

#include <SFML/Graphics.hpp>
#include <Entities/Camera.hpp>

#include "Camera.hpp"
#include "Window.hpp"
#include "inputKeys.hpp"

namespace fender::systems::SFMLSystems
{
    void Camera::init()
    {
        __init();
        addReaction<ResponseWindow>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<ResponseWindow>(pkg);
            camToWindow[packet.camera] = packet.window;
        });
        addReaction<futils::Keys>([this](futils::IMediatorPacket &pkg){
            auto &key = futils::Mediator::rebuild<futils::Keys>(pkg);
            auto step = 0.1;
            if (key == futils::Keys::ArrowRight)
            {
                auto cams = entityManager->get<components::Camera>();
                for (auto &cam : cams)
                {
                    if (cam->activated)
                    {
                        auto &pos = cam->getEntity().get<components::Transform>();
                        pos.position.x += step;
                    }
                }
            }
            else if (key == futils::Keys::ArrowLeft)
            {
                auto cams = entityManager->get<components::Camera>();
                for (auto &cam : cams)
                {
                    if (cam->activated)
                    {
                        auto &pos = cam->getEntity().get<components::Transform>();
                        pos.position.x -= step;
                    }
                }
            }
            else if (key == futils::Keys::ArrowUp)
            {
                auto cams = entityManager->get<components::Camera>();
                for (auto &cam : cams)
                {
                    if (cam->activated)
                    {
                        auto &pos = cam->getEntity().get<components::Transform>();
                        pos.position.y -= step;
                    }
                }
            }
            else if (key == futils::Keys::ArrowDown)
            {
                auto cams = entityManager->get<components::Camera>();
                for (auto &cam : cams)
                {
                    if (cam->activated)
                    {
                        auto &pos = cam->getEntity().get<components::Transform>();
                        pos.position.y += step;
                    }
                }
            }
        });
        phase = Run;
    }

    void Camera::renderWindow(futils::IEntity &cam)
    {
        auto win = camToWindow[&cam];
        if (win)
        {
            drawCamCrosshair(cam.get<components::Camera>(), win);
            win->display();
        }
    }

    void Camera::drawCamCrosshair(components::Camera &cam, sf::RenderWindow *window)
    {
        if (cam.debugMode == false)
            return;
        auto worlds = entityManager->get<components::World>();
        int crossHairSize = 10;
        if (!worlds.empty()) {
            auto &world = worlds.front();
            crossHairSize = world->unit / 2;
        }
        if (window != nullptr) {
            sf::Vertex vertical[] = {
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2 - crossHairSize)),
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2 + crossHairSize))
            };
            sf::Vertex horizontal[] = {
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2 - crossHairSize, window->getSize().y / 2)),
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2 + crossHairSize, window->getSize().y / 2))
            };
            window->draw(vertical, 2, sf::Lines);
            window->draw(horizontal, 2, sf::Lines);
        }
    }

    void Camera::renderCam(futils::IEntity &entity, components::Camera &cam, components::World &world)
    {
        RequestWindow request;
        request.camera = &entity;
        events->send<RequestWindow>(request);

        // camToWindow est update par la reaction a ResponseWindow
        auto realWindow = camToWindow[&entity];
        // Si tout va bien, on peut commencer a render, donc on clear.
        if (realWindow) {
            ClearWindow cw;
            cw.camera = &entity;
            events->send<ClearWindow>(cw);
        } else
        {
            events->send<std::string>("Cannot render because Camera system failed to find realWindow");
            return ;
        }
        auto &camPos = entity.get<components::Transform>();
        int currentLayer = camPos.position.z - cam.viewDistance;

        while (currentLayer < camPos.position.z)
        {
            RenderLayer event;
            event.layer = currentLayer;
            event.camData = &cam;

            auto range = layout.equal_range(currentLayer);
            int rangeCount = 0;
            for (auto it = range.first; it != range.second; it++)
            {
                rangeCount++;
                auto &absolute = it->second->get<components::AbsoluteTransform>();
                auto &transform = it->second->get<components::Transform>();
                auto windowSize = realWindow->getSize();
                auto unit = world.unit;
                auto zoom = 1; // TODO : add zoom

                absolute.position.x = (int)(windowSize.x / 2 + (transform.position.x - camPos.position.x) * unit * zoom);
                absolute.position.y = (int)(windowSize.y / 2 + (transform.position.y - camPos.position.y) * unit * zoom);
                absolute.size.x = (int)(transform.size.x * unit * zoom);
                absolute.size.y = (int)(transform.size.y * unit * zoom);
//                if ((absolute.position.x > 0 && absolute.position.y > 0
//                     && absolute.position.x < (int)windowSize.x && absolute.position.y < (int)windowSize.y)
//                    || (absolute.position.x + absolute.size.w > 0 && absolute.position.x + absolute.size.w < (int)windowSize.x)
//                    || (absolute.position.y + absolute.size.h > 0 && absolute.position.y + absolute.size.h < (int)windowSize.y))
                event.objects.push_back(it->second);
            }
            event.window = realWindow;
            events->send<RenderLayer>(event);
            currentLayer++;
        }
        AllLayersRendered allLayersRendered;
        allLayersRendered.camData = &cam;
        allLayersRendered.window = realWindow;
        events->send<AllLayersRendered>(allLayersRendered);
        renderWindow(entity);
    }

    void Camera::renderEachCam() {
        auto cameras = entityManager->get<components::Camera>();
        auto worlds = entityManager->get<components::World>();
        if (worlds.empty())
            return ;
        auto &world = worlds.front();
        // Pour toutes les cameras
        for (auto &cam: cameras)
        {
            auto &entity = cam->getEntity();
            // Si la cam doit render
            if (cam->activated && cam->window) {
                renderCam(entity, *cam, *world);
            }
        }
    }

    void Camera::sortGameObjects() {
        layout.clear();
        auto gameObjects = entityManager->get<components::GameObject>();
        for (auto &go: gameObjects)
        {
            auto &entity = go->getEntity();
            auto &transform = entity.get<components::Transform>();
            layout.insert(std::pair<int, futils::IEntity *>(transform.position.z, &entity));
        }
    }

    void Camera::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run:
                sortGameObjects();
                renderEachCam();
                return ;
        }
    }
}
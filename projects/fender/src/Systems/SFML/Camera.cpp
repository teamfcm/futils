//
// Created by arroganz on 1/3/18.
//

#include <SFML/Graphics.hpp>
#include <Components/World.hpp>

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
            auto worlds = entityManager->get<components::World>();
            int step = 1;
            if (!worlds.empty())
                step = worlds.front()->unit / 3;
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

    void Camera::renderEachCam() {
        auto cameras = entityManager->get<components::Camera>();
        for (auto &cam: cameras)
        {
            auto &entity = cam->getEntity();
            if (cam->activated && cam->window)
            {
                RequestWindow request;
                request.camera = &entity;
                events->send<RequestWindow>(request);
                auto realWindow = camToWindow[&entity];
                if (realWindow) {
                    ClearWindow cw;
                    cw.camera = &entity;
                    events->send<ClearWindow>(cw);
                }
                auto &camPos = entity.get<components::Transform>();
                int currentLayer = camPos.position.z - cam->viewDistance;

                while (currentLayer < camPos.position.z)
                {
                    RenderLayer event;
                    event.layer = currentLayer;
                    event.camData = cam;
                    auto range = layout.equal_range(currentLayer);
                    for (auto it = range.first; it != range.second; it++)
                    {
                        event.objects.push_back(it->second);
                    }
                    event.window = realWindow;
                    events->send<RenderLayer>();
                    currentLayer++;
                }
                AllLayersRendered allLayersRendered;
                allLayersRendered.camData = cam;
                allLayersRendered.window = realWindow;
                events->send<AllLayersRendered>(allLayersRendered);
                renderWindow(entity);
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
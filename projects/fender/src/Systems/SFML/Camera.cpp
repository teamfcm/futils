//
// Created by arroganz on 1/3/18.
//

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Window.hpp"

namespace fender::systems::SFMLSystems
{
    void Camera::init()
    {
        __init();
        addReaction<ResponseWindow>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<ResponseWindow>(pkg);
            camToWindow[packet.camera] = packet.window;
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
        if (window != nullptr) {
            sf::Vertex vertical[] = {
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2 - 10)),
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2 + 10))
            };
            sf::Vertex horizontal[] = {
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2 - 10, window->getSize().y / 2)),
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2 + 10, window->getSize().y / 2))
            };
            (void)horizontal;
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
                events->send(allLayersRendered);
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
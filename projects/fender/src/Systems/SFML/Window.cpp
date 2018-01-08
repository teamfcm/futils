//
// Created by arroganz on 1/1/18.
//

#include "Components/Window.hpp"
#include "Window.hpp"
#include "Entities/Camera.hpp"
#include "Camera.hpp"

namespace fender::systems::SFMLSystems
{
    void Window::requireEvents()
    {
        addReaction<ClearWindow>([this](futils::IMediatorPacket &pkg) {
            auto &packet = futils::Mediator::rebuild<ClearWindow>(pkg);
            auto &entity = packet.camera;
            auto &cam = entity->get<components::Camera>();
            auto window = cam.window;
            auto &winCompo = window->get<components::Window>();
            auto realWindow = _windows.at(&winCompo).win;
            sf::Color color;
            color << winCompo.getEntity().get<components::Color>().color;
            realWindow->clear(color);
        });
        addReaction<RequestWindow>([this](futils::IMediatorPacket &pkg){
            auto &request = futils::Mediator::rebuild<RequestWindow>(pkg);
            auto &entity = request.camera;
            auto &cam = entity->get<components::Camera>();
            auto window = cam.window;
            auto &winCompo = window->get<components::Window>();
            ResponseWindow response;
            response.camera = entity;
            response.window = _windows.at(&winCompo).win;
            events->send<ResponseWindow>(response);
        });
        addReaction<futils::ComponentAttached<Component>>([this](futils::IMediatorPacket &pkg){
            auto components = entityManager->get<Component>();
            auto &packet = futils::Mediator::rebuild<futils::ComponentAttached<Component>>(pkg);
            for (auto &win: components)
            {
                if (win->title == packet.compo.title)
                    onNewWindow(*win);
            }
        });
        addReaction<futils::ComponentDeleted<Component>>([this](futils::IMediatorPacket &pkg){
            auto components = entityManager->get<Component>();
            auto &packet = futils::Mediator::rebuild<futils::ComponentDeleted<Component>>(pkg);
            for (auto &win: components)
            {
                if (win->title == packet.compo.title)
                    onWindowDestroyed(*win);
            }
        });
    }

    void Window::onWindowDestroyed(Component &win)
    {
        std::cout << "Trying to close : " << win.title << " at " << &win << std::endl;
        if (_windows.find(&win) == _windows.end())
            return ;
        auto &real = _windows.at(&win);
        close(real);
    }

    void Window::onNewWindow(Component &win)
    {
        auto &real = _windows[&win];
        std::cout << "Stored new window " << win.title << " at " << &win << std::endl;
        real.data = &win;
        auto mode = sf::VideoMode::getDesktopMode();
        win.screenSize.w = mode.width;
        win.screenSize.h = mode.height;
    }

    void Window::init()
    {
        __init();
        phase = RUN;
        requireEvents();
    }

    void Window::open(RealWindow &real)
    {
        if (real.win != nullptr)
            return ;
        auto &data = *real.data;
        if (real.win == nullptr)
        {
            real.win = new sf::RenderWindow(sf::VideoMode(data.size.w, data.size.h), data.title);
            real.win->setFramerateLimit(60);
            if (real.win->isOpen()) {
                data.isOpen = true;
                data.isClose = false;
            }
            real.copy = *real.data;
        }
    }

    void Window::close(RealWindow &real)
    {
        if (real.win == nullptr)
            return ;
        auto &data = *real.data;
        if (real.win != nullptr)
        {
            real.win->close();
            data.isOpen = false;
            data.isClose = true;
        }
    }

    void Window::pollEvents(RealWindow &real)
    {
        if (real.win == nullptr)
            return ;

        sf::Event event;
        int count{0};

        while (real.win->pollEvent(event)) {
            events->send<sf::Event>(event);
            count++;
        }
    }

    void Window::updateTitle(RealWindow &real)
    {
        if (real.win == nullptr)
            return ;

        if (real.copy.title != real.data->title)
        {
            real.win->setTitle(real.data->title);
            real.copy.title = real.data->title;
        }
    }

    void Window::run(float)
    {
        switch (phase)
        {
            case INIT: return init();
            case RUN:
                for (auto &pair: _windows)
                {
                    auto &real = pair.second;
                    if (real.data->visible)
                        open(real);
                    else
                        close(real);
                    updateTitle(real);
                    pollEvents(real);
                }
                return ;
        }
    }
}
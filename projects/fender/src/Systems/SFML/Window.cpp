//
// Created by arroganz on 1/1/18.
//

#include "Components/Window.hpp"
#include "Window.hpp"

namespace fender::systems::SFMLSystems
{
    void Window::requireEvents()
    {
        addReaction<futils::ComponentAttached<Component>>([this](futils::IMediatorPacket &pkg){
            auto components = entityManager->get<Component>();
            auto &packet = futils::Mediator::rebuild<futils::ComponentAttached<Component>>(pkg);
            for (auto &win: components)
            {
                if (win->title == packet.compo.title)
                    onNewWindow(*win);
            }
        });
        // TODO: ComponentDeleted event
//        addReaction<futils::ComponentDeleted<Window_c>([this](futils::IMediatorPacket &pkg){
//            onWindowDestroyed(pkg);
//        });
    }

    void Window::onWindowDestroyed(Component &win)
    {
        _windows.erase(win.title);
    }

    void Window::onNewWindow(Component &win)
    {
        auto &real = _windows[win.title];
        real.data = &win;
        auto mode = sf::VideoMode::getDesktopMode();
        win.screenSize.w = mode.width;
        win.screenSize.h = mode.height;
        std::cout << "New Win : " << win.title << std::endl;
    }

    void Window::init()
    {
        __init();
        phase = RUN;
        requireEvents();
    }

    void Window::open(RealWindow &real)
    {
        auto &data = *real.data;
        if (real.win == nullptr)
        {
            real.win = new sf::RenderWindow(sf::VideoMode(data.size.w, data.size.h), data.title);
            if (real.win->isOpen()) {
                data.isOpen = true;
                data.isClose = false;
            }
        }
    }

    void Window::close(RealWindow &real)
    {
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
        sf::Event event;
        int count{0};

        while (real.win->pollEvent(event)) {
            events->send<sf::Event>(event);
            count++;
        }
        if (count > 0)
            events->send<std::string>("Processed " + std::to_string(count) + " events for window " + real.data->title);
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
                    if (real.data->visible && !real.data->isOpen)
                        open(real);
                    else if (!real.data->visible && real.data->isOpen)
                        close(real);
                    pollEvents(real);
                }
                return ;
        }
    }
}
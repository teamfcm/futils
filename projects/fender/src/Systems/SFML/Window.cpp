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
        _windows[win.title] = &win;
        auto mode = sf::VideoMode::getDesktopMode();
        win.screenSize.w = mode.width;
        win.screenSize.h = mode.height;
    }

    void Window::init()
    {
        phase = RUN;
        requireEvents();
    }

    void Window::open(Component &)
    {
        
    }

    void Window::close(Component &)
    {

    }

    void Window::run(float)
    {
        switch (phase)
        {
            case INIT: return init();
            case RUN:
                for (auto &pair: _windows)
                {
                    auto win = pair.second;
                    if (win->visible && !win->isOpen)
                        open(*win);
                    if (!win->visible && win->isOpen)
                        close(*win);
                }
                return ;
        }
    }
}
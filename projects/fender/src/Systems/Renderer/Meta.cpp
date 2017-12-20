//
// Created by arroganz on 12/19/17.
//

#include "Meta.hpp"
#include "../../Components/Meta.hpp"
#include "fender.hpp"
#include "events.hpp"
#include "../../Components/Box.hpp"
#include "SFMLRenderer.hpp"

namespace {
    std::unordered_map<futils::WStyle, sf::Uint32> sfStyles = {
            {futils::WStyle::None, sf::Style::None},
            {futils::WStyle::Titlebar, sf::Style::Titlebar},
            {futils::WStyle::Fullscreen, sf::Style::Fullscreen},
            {futils::WStyle::Resize, sf::Style::Resize},
            {futils::WStyle::Close, sf::Style::Close},
            {futils::WStyle::Default, sf::Style::Default}
    };
}

namespace fender::systems
{
    void Meta::createNewWindow(fender::components::Meta const &meta)
    {
        if (windows.find(meta.getName()) == windows.end())
        {
            try {
                auto &ent = meta.getEntity();
                auto &box = ent.get<fender::components::Box>();
                unsigned int x,y,w,h = 0;
                auto style = meta.getStyle();

                if (box.isRelative()) {
                    auto &size = box.getRSize();
                    auto &pos = box.getRPos();
                    auto desktop = sf::VideoMode::getDesktopMode();

                    w = (!box.isRelative() ? (unsigned int)size.w : size.w * desktop.width);
                    h = (!box.isRelative() ? (unsigned int)size.h : size.h * desktop.height);
                    x = (!box.isRelative() ? (unsigned int)pos.x : pos.x * desktop.width);
                    y = (!box.isRelative() ? (unsigned int)pos.y : pos.y * desktop.height);
                } else {
                    auto &size = box.getSize();
                    auto &pos = box.getPos();

                    w = (unsigned int)size.w;
                    h = (unsigned int)size.h;
                    x = (unsigned int)pos.x;
                    y = (unsigned int)pos.y;
                }
                auto win = new sf::RenderWindow(sf::VideoMode(w, h),
                                                 meta.getName(), sfStyles[style]);
                win->setPosition(sf::Vector2i(x, y));
                Meta::window windowInfo;
                windowInfo._win = win;
                windowInfo._meta = &meta;
                windows[meta.getName()] = windowInfo;
                std::cout << "Meta created " << meta << std::endl;
                events->send(fender::events::MetaCreated(meta.getName()));
                win->setFramerateLimit(60);
            } catch (std::runtime_error const &)
            {
                // events->send<futils::MetaError>(error.what());
            }
        }
    }

    void Meta::init()
    {
        events->require<futils::ComponentAttached<fender::components::Meta>>(this, [this](futils::IMediatorPacket &pkg)
        {
            auto &m = futils::Mediator::rebuild<futils::ComponentAttached<fender::components::Meta>>(pkg);
            createNewWindow(m.compo);
        });
        phase = RUN;
    }

    void Meta::refreshMetas(float)
    {
        for (auto &pair: windows)
        {
            auto &windowInfos = pair.second;
            auto &w = *windowInfos._win;
            if (!w.isOpen())
            {
                // TODO: Should emit an event
                return ;
            }
            sf::Color color;
            color << windowInfos._meta->getColor();
            w.clear(color);

            // Event processing
            sf::Event event;
            while (w.pollEvent(event))
            {
                // Request for closing the window
                if (event.type == sf::Event::Closed) {
                    // TODO: Should emit an event !
                    w.close();
                }
            }

            w.display();
        }
    }

    void Meta::run(float elapsed) {
        switch (phase)
        {
            case INIT: return init();
            case RUN: return refreshMetas(elapsed);
        }
    }
}
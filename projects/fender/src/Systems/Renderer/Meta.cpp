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
                auto &size = box.getSize();
                auto &pos = box.getPos();
                auto style = meta.getStyle();

                auto desktop = sf::VideoMode::getDesktopMode();
                auto w = (unsigned int)(size.w > 1.0 ? size.w : size.w * desktop.width);
                auto h = (unsigned int)(size.h > 1.0 ? size.h : size.h * desktop.height);
                auto x = (unsigned int)(pos.x > 1.0 || pos.x == 0 ? pos.x : pos.x * desktop.width);
                auto y = (unsigned int)(pos.y > 1.0 || pos.y == 0 ? pos.y : pos.y * desktop.height);

                auto rwin = new sf::RenderWindow(sf::VideoMode(w, h),
                                                 meta.getName(), sfStyles[style]);
                rwin->setPosition(sf::Vector2i(x, y));
                Meta::window windowInfo;
                windowInfo._win = rwin;
                windowInfo._meta = &meta;
                windows[meta.getName()] = windowInfo;
                std::cout << "Meta created " << meta << std::endl;
                events->send(fender::events::MetaCreated(meta.getName()));
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
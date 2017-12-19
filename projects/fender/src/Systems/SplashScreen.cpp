//
// Created by arroganz on 12/17/17.
//

#include <fender.hpp>
#include "SplashScreen.hpp"
#include "../Entities/Window.hpp"

fender::systems::SplashScreen::SplashScreen()
{

}

void fender::systems::SplashScreen::init() {
    phase++;
    events->require<fender::events::MetaCreated>(this, [this](futils::IMediatorPacket &pkg){
        auto &win = futils::Mediator::rebuild<fender::events::MetaCreated>(pkg);
        events->send<std::string>("SplashScreen is happy : " + win.name);
        phase++;
    });
}

void fender::systems::SplashScreen::requestWindow()
{
    // garder win en membre de splashcreen evidemment !
    auto &win = entityManager->create<fender::entities::Window>("Fender SplashScreen",
                                                    futils::Vec2<futils::Pct>(28, 33),
                                                    futils::Vec2<futils::Pct>(45, 33),
                                                    futils::WStyle::None);
    auto &bg = win.get<fender::components::Meta>();
    bg.setColor(futils::Granite);
    phase++;
}

void fender::systems::SplashScreen::run(float)
{
    switch (phase) {
        case 0: return init();
        case 1: return requestWindow();
        case 2: return ;
    }
}
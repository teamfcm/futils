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
    phase = 1;
    events->require<fender::events::MetaCreated>(this, [this](futils::IMediatorPacket &pkg){
        auto &win = futils::Mediator::rebuild<fender::events::MetaCreated>(pkg);
        events->send<std::string>("SplashScreen is happy : " + win.name);
    });
}

void fender::systems::SplashScreen::requestWindow()
{
    win = &entityManager->create<fender::entities::Window>("Fender SplashScreen",
                                                    futils::Vec2<futils::Pct>(33, 33),
                                                    futils::Vec2<futils::Pct>(33, 33),
                                                    futils::WStyle::None);
    auto &meta = win->get<fender::components::Meta>();
    meta.setColor(futils::Granite);
    phase = 2;
}

void fender::systems::SplashScreen::run(float)
{
    // TODO: stateMachine.run();
    switch (phase) {
        case 0: return init();
        case 1: return requestWindow();
        case 2: return ;
    }
}

//
// Created by arroganz on 12/17/17.
//

#include <fender.hpp>
#include "SplashScreen.hpp"

fender::systems::SplashScreen::SplashScreen()
{

}

void fender::systems::SplashScreen::init() {
    phase++;
    events->require<fender::events::WindowOpened>(this, [this](futils::IMediatorPacket &){
        events->send<std::string>("SplashScreen is happy :)");
        phase++;
    });
}

void fender::systems::SplashScreen::requestWindow()
{
    requests::OpenWindow ow;
    ow.size.w = 1.0/3.0;
    ow.size.h = 1.0/3.0;
    ow.pos.x = 1.0/2.0 - (ow.size.w / 2.0);
    ow.pos.y = 1.0/2.0 - (ow.size.h / 2.0);
    ow.style = futils::WStyle::None;
    ow.color = futils::Granite;
    events->send<requests::OpenWindow>(ow);
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
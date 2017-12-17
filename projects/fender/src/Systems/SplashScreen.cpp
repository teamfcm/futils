//
// Created by arroganz on 12/17/17.
//

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
    ow.pos.x = 100;
    ow.pos.y = 200;
    ow.size.w = 200;
    ow.size.h = 200;
    events->send<requests::OpenWindow>(ow);
}

void fender::systems::SplashScreen::run(float)
{
    switch (phase) {
        case 0: return init();
        case 1: return requestWindow();
        case 2: return ;
    }
}
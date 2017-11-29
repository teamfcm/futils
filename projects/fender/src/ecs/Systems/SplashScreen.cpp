//
// Created by arroganz on 11/27/17.
//

# include "systems.hpp"

fender::systems::SplashScreen::SplashScreen()
{
    name = "SplashScreen";
};

void fender::systems::SplashScreen::run(float)
{
    if (phase == 0) {
        events->require<events::WindowOpened>((void *)this, [this](futils::IMediatorPacket &pkg) {
            auto &wo = static_cast<events::WindowOpened &>(pkg);
            LOUT("Window opened with name " + wo.name);
            this->phase = 2;
        });
        phase = 1;
    } else if (phase == 1) {
        fender::requests::OpenWindow ow;
        ow.name = "WindowName";
        ow.height = 200;
        ow.width = 200;
        events->send(ow);
    }
}
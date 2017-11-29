//
// Created by arroganz on 11/27/17.
//

# include "systems.hpp"

fender::systems::SplashScreen::SplashScreen():
        config("./config/fender.ini")
{
    name = "SplashScreen";
};

void fender::systems::SplashScreen::init() {
    events->require<events::WindowOpened>((void *)this, [this](futils::IMediatorPacket &pkg) {
        auto &wo = static_cast<events::WindowOpened &>(pkg);
        LOUT("Window opened with name " + wo.name);
        this->phase = 2;
    });
    phase = 1;
}

void fender::systems::SplashScreen::openWindow()
{
    fender::requests::OpenWindow ow;
    ow.name = "WindowName";
    ow.height = 1.0 / 3.0;
    ow.width = 1.0 / 2.0;
    events->send(ow);
}

void fender::systems::SplashScreen::changeBackground()
{
    entityManager->create<Background>(config["splashscreen"]["background-image"]);
    phase = 3;
}

void fender::systems::SplashScreen::run(float)
{
    switch (phase) {
        case 0:
            init();
            break ;
        case 1:
            openWindow();
            break ;
        case 2:
            changeBackground();
            break ;
    }
}
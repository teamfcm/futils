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
    events->require<fender::events::WindowOpened>(this, [this](futils::IMediatorPacket &){
        events->send<std::string>("SplashScreen is happy :)");
        phase++;
    });
}

void fender::systems::SplashScreen::requestWindow()
{
    // garder win en membre de splashcreen evidemment !
    auto &win = entityManager->create<fender::entities::Window>("Fender SplashScreen",
                                                    futils::Vec2<int>(25, 25),
                                                    futils::Vec2<int>(800, 600),
                                                    futils::WStyle::None);
    auto &bg = win.get<fender::components::Meta>();
    bg.setColor(futils::Manganeseblue);
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
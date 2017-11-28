//
// Created by arroganz on 11/27/17.
//

# include "systems.hpp"

fender::systems::SplashScreen::SplashScreen()
{

};

void fender::systems::SplashScreen::run(float)
{
    static int i = 0;
    if (i == 0) {
        auto &window = entityManager->createEntity<Window>();
        auto &win = window.get<components::Windowed>();
        win.rename("Window");
        win.setSize(200, 200);
        i++;
    }
}
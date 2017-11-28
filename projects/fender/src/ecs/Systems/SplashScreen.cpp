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
        entityManager->createEntity<Window>("Window", 200, 200);
        i++;
    }
}
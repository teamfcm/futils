//
// Created by arroganz on 11/27/17.
//

# include "systems.hpp"

fender::systems::SplashScreen::SplashScreen()
{
    _win.reset(entityManager->createEntity<Window>("Name", 200, 200));
};

void fender::systems::SplashScreen::run(float)
{
    LOUT("Coucou");
}
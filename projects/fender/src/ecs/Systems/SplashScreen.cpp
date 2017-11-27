//
// Created by arroganz on 11/27/17.
//

# include "fender.hpp"

fender::systems::SplashScreen::SplashScreen()
{

};

void fender::systems::SplashScreen::run(float)
{
    LOUT("Coucou");
    entityManager->removeSystem(name);
}
//
// Created by arroganz on 11/24/17.
//

# include "App.hpp"

demo::App::App(int, char *argv[]):
        execPath(argv[0])
{

}

int demo::App::start() {
    // engine.addSystem(fender::systems::SplashScreen);
    return engine.start(execPath);
}

int demo::App::run() {
    return engine.run();
};
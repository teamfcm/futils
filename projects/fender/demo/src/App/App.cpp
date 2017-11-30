//
// Created by arroganz on 11/24/17.
//

# include "dloader.hpp"
# include "App.hpp"
# include "systems.hpp"

demo::App::App(int, char *argv[]):
        execPath(argv[0])
{
    auto lib = futils::Dloader("../release/libfender.so");
    auto enginePtr = lib.build<fender::Fender>(execPath);
    engine.reset(enginePtr);
}

int demo::App::start() {
    if (engine->start() != 0)
        return -1;
    return 0;
}

int demo::App::run() {
    engine->addSystem<fender::systems::SplashScreen>();
    return engine->run();
};
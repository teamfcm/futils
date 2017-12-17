//
// Created by arroganz on 11/24/17.
//

# include "App.hpp"

demo::App::App(int, char *argv[]):
        execPath(argv[0])
{
	engine = std::make_unique<fender::Fender>(execPath);
}

int demo::App::start() {
    if (engine->start() != 0)
        return -1;
    return 0;
}

int demo::App::run() {
    return engine->run();
};
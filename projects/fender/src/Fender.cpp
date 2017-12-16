//
// Created by arroganz on 11/26/17.
//

# include "fender.hpp"
# include "goToBinDir.hpp"
# include "Systems/Log.hpp"

extern "C" fender::Fender *Fender(std::string const &execPath) {
    return new fender::Fender(execPath);
}

fender::Fender::Fender(std::string const &arg0) {
    futils::goToBinDir(arg0);

    entityManager = std::make_unique<futils::EntityManager>();
    events = std::make_unique<futils::Mediator>();
    entityManager->provideMediator(*events);
}

struct shutdown {
    std::string const &msg;
    shutdown(std::string const &msg): msg(msg) {}
};

void fender::Fender::loadSystemDir(std::string const &path)
{
    events->send<std::string>("Loading systems in " + path);
    events->send<shutdown>(std::string("Shutdown"));
}

int fender::Fender::start() {
    addSystem<systems::Log>();
    LOUT(std::to_string(entityManager->getNumberOfSystems()) + " systems loaded.");
    loadSystemDir("./systems");
    return 0;
}

int fender::Fender::run() {
    int runs = 0;
    for (;entityManager->getNumberOfSystems() > 0; runs++) {
        entityManager->run();
    }
    LOUT("Manager done running. Ran " + std::to_string(runs) + " times.");
    return 0;
}

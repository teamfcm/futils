//
// Created by arroganz on 11/26/17.
//

# include "fender.hpp"
# include "goToBinDir.hpp"
# include "Systems/Log.hpp"
# include "Systems/SFML/SFMLRenderer.hpp"

extern "C" fender::Fender *Fender(std::string const &execPath) {
    return new fender::Fender(execPath);
}

fender::Fender::Fender(std::string const &arg0) {
    futils::goToBinDir(arg0);

    entityManager = std::make_unique<futils::EntityManager>();
    events = std::make_unique<futils::Mediator>();
    entityManager->provideMediator(*events);
}

void fender::Fender::loadSystemDir(std::string const &path)
{
    events->send<std::string>("Loading systems in " + path);
}

int fender::Fender::start() {
    addSystem<systems::Log>();
    addSystem<systems::SFMLRenderer>();
    LOUT(std::to_string(entityManager->getNumberOfSystems()) + " systems loaded.");
    return entityManager->run(); // this will init all systems
}

int fender::Fender::run() {
    int64_t runs = 0;
    for (;entityManager->getNumberOfSystems() > 0; runs++) {
        if (entityManager->run() != 0)
            break ;
    }
    events->send<events::Shutdown>();
    events->send<std::string>("Fender shutting down. Ran " + std::to_string(runs) + " times.");
    return 0;
}

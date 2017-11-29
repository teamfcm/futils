//
// Created by arroganz on 11/26/17.
//

# include "fender.hpp"
# include "goToBinDir.hpp"
# include "dloader.hpp"

fender::Fender::Fender(std::string const &arg0) {
    futils::goToBinDir(arg0);
    futils::Ini config("./config/fender.ini");
    START_LOG(config["global"]["logfile"]);

    lib = std::make_unique<futils::Dloader>(config["global"]["fenderPath"]);
    auto build = lib->build<Manager, futils::Ini const &>(config);
    if (build == nullptr) {
        throw std::runtime_error("Cannot build library");
    }
    manager.reset(build);
    entityManager = std::make_unique<futils::EntityManager>();
    events = std::make_unique<futils::Mediator>();
    entityManager->provideMediator(*events);
    manager->provideEntityManager(*entityManager);
    manager->provideMediator(*events);
}

int fender::Fender::start() {
    return manager->start();
}

int fender::Fender::run() {
    return manager->run();
}

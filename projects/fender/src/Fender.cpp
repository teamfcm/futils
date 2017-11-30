//
// Created by arroganz on 11/26/17.
//

# include "fender.hpp"
# include "goToBinDir.hpp"
# include "systems.hpp"

//#ifdef linux
	extern "C" fender::Fender *Fender(std::string const &execPath) {
		return new fender::Fender(execPath);
	}
//#elif _WIN32
//	fender::Fender *__declspec(dllexport) __stdcall Fender(std::string const &execPath) {
//		return new fender::Fender(execPath);
//	}
//#endif linux

fender::Fender::Fender(std::string const &arg0) {
    futils::goToBinDir(arg0);
    // futils::Ini config("./config/fender.ini");

    entityManager = std::make_unique<futils::EntityManager>();
    events = std::make_unique<futils::Mediator>();
    entityManager->provideMediator(*events);
}

int fender::Fender::start() {
    entityManager->addSystem<fender::systems::WindowManager>();
    entityManager->addSystem<fender::systems::Renderer>();
    entityManager->addSystem<fender::systems::Image>();
    entityManager->addSystem<fender::systems::Transform>();
    LOUT(std::to_string(entityManager->getNumberOfSystems()) + " systems loaded.");
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

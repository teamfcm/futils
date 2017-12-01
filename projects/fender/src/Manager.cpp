//
// Created by ganz on 16/08/17.
//

#ifdef unix
# include <unistd.h>
#endif
# include <callback.hpp>
# include "fender.hpp"
# include "systems.hpp"
# include "log.hpp"
# include "SFMLRender.hpp"
# include "CursesRender.hpp"
# include "ini.hpp"
# include "clock.hpp"

//extern "C"
//fender::Manager *Manager(futils::Ini &config)
//{
//    return new fender::Manager(config);
//}
//
//fender::Manager::Manager(futils::Ini &config):
//        config(config)
//{
//
//}
//
//int fender::Manager::start()
//{
//    entityManager->addSystem<fender::systems::WindowManager>();
//    entityManager->addSystem<fender::systems::Renderer>();
//    entityManager->addSystem<fender::systems::Image>();
//    entityManager->addSystem<fender::systems::Transform>();
//    LOUT(std::to_string(entityManager->getNumberOfSystems()) + " systems loaded.");
//    LOUT("Manager started : OK");
//    return 0;
//}
//
//int fender::Manager::run()
//{
//    int runs = 0;
//    for (;entityManager->getNumberOfSystems() > 0; runs++) {
//        entityManager->run();
//    }
//    LOUT("Manager done running. Ran " + std::to_string(runs) + " times.");
//    return status;
//}
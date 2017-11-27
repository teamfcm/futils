//
// Created by ganz on 16/08/17.
//

# include <unistd.h>
#include <callback.hpp>
# include "fender.hpp"
# include "log.hpp"
# include "SFMLRender.hpp"
# include "CursesRender.hpp"
# include "ini.hpp"
# include "clock.hpp"

extern "C"
fender::Manager *Manager(futils::Ini &config)
{
    return new fender::Manager(config);
}

fender::Manager::Manager(futils::Ini &config):
        config(config)
{
    this->renderingBuilders["SFML"] = []() {
        return std::make_unique<fender::SFMLRender>();
    };
    this->renderingBuilders["NCURSES"] = []() {
        return std::make_unique<fender::CursesRender>();
    };

    auto global = config["global"];
    auto conf = config["fender"];
    std::string renderLibrary = global["RenderLibrary"];
    LOUT("Selected RenderLibrary : " + renderLibrary);
    if (!(this->renderer = this->renderingBuilders[renderLibrary]()))
        throw std::runtime_error("Failed To Build " + std::string(global["RenderLibrary"]));
    LOUT("Rendering Built Successfully.");
    if (static_cast<bool>(conf["SmartMode"]) == true)
        this->renderer->SmartModeInit(config);
}

int fender::Manager::start()
{
    LOUT(std::to_string(entityManager->getNumberOfSystems()) + " systems loaded.");
    LOUT("Manager started : OK");
    return 0;
}

int fender::Manager::run()
{
    int runs = 0;
    for (;entityManager->getNumberOfSystems() > 0; runs++) {
        entityManager->run();
    }
    LOUT("Manager done running. Ran " + std::to_string(runs) + " times.");
    return status;
}
//
// Created by ganz on 16/08/17.
//

# include "fender.hpp"
# include "flog.hpp"
# include "sfml/SFMLRender.hpp"
# include "ncurses/CursesRender.hpp"
# include "Fini.hpp"
# include <unistd.h>

extern "C"
fender::Manager *manager(fender::ISceneFactory &fact,
                         futils::INI::INIProxy *configProxy)
{
    return new fender::Manager(fact, configProxy);
}

fender::Manager::Manager(ISceneFactory &fact,
                         futils::INI::INIProxy *configProxy):
        sceneFactory(fact),
        config(configProxy),
        timeline("Scenes/timeline.ini")
{
    this->renderingBuilders["SFML"] = []()
    {
        return std::make_unique<fender::SFMLRender>();
    };
    this->renderingBuilders["NCURSES"] = []()
    {
        return std::make_unique<fender::CursesRender>();
    };

    auto global = (*this->config)["global"];
    auto conf = (*this->config)["fender"];
    std::string renderLibrary = global["RenderLibrary"];
    LOUT("Selected RenderLibrary : " + renderLibrary);
    if (!(this->renderer = this->renderingBuilders[renderLibrary]()))
        throw std::runtime_error("Failed To Build " + global["RenderLibrary"]);
    LOUT("Renderer Built Successfully.");
    if (conf["SmartMode"] == true)
        this->renderer->SmartModeInit(*this->config);
}

void    fender::Manager::start()
{
//    TODO: This should be from a ini file
    auto scene = this->sceneFactory.build("intro");
    if (scene)
    {
        scene->provideRenderer(*this->renderer);
        scene->init();
        while (scene->isDone() == false
                && this->renderer->isRunning())
        {
            this->renderer->pollEvents();
            scene->update();
            this->renderer->refresh();
            usleep(20000);
        }
    }
}

void    fender::Manager::run()
{

}
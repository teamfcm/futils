//
// Created by ganz on 16/08/17.
//

# include "fender.h"
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
    auto conf = *this->config;

    if (conf["fender"]["SmartMode"] == true)
        this->runConfigBuild();
}

void fender::Manager::runConfigBuild()
{
    auto conf = *this->config;

    this->renderer = this->renderingBuilders[conf["fender"]["RenderLibrary"]]();
}

void    fender::Manager::start()
{
    auto scene = this->sceneFactory.build("intro");
    if (scene)
    {
        scene->provideRenderer(*this->renderer);
        scene->init();
        while (scene->isDone() == false
                && this->renderer->isRunning())
        {
            scene->update();
            this->renderer->refresh();
            usleep(5000);
        }
    }
}

void    fender::Manager::run()
{

}
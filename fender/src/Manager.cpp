//
// Created by ganz on 16/08/17.
//

# include "fender.h"
# include "flog.hpp"
# include "sfml/SFMLRender.hpp"
# include "ncurses/CursesRender.hpp"
# include <unistd.h>

extern "C" fender::Manager *manager(fender::ISceneFactory &fact)
{
    return new fender::Manager(fact);
}

fender::Manager::Manager(ISceneFactory &fact): sceneFactory(fact)
{
    this->renderer = std::make_unique<fender::SFMLRender>("config.json");
}

void    fender::Manager::loadConfig(std::string const &configFile)
{
    LOUT("loading config from " + configFile);
}

void    fender::Manager::loadTimeline(std::string const &timelineFile)
{
    LOUT("loading timeline from " + timelineFile);
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
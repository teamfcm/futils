//
// Created by ganz on 16/08/17.
//

# include "fender.h"
# include "flog.hpp"

extern "C" fender::Manager *manager(fender::ISceneFactory &fact)
{
    return new fender::Manager(fact);
}

fender::Manager::Manager(ISceneFactory &fact): sceneFactory(fact)
{
    std::cout << "coucou" << std::endl;
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
        scene->update();
}

void    fender::Manager::run()
{

}
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
        throw std::runtime_error("Failed To Build " + std::string(global["RenderLibrary"]));
    LOUT("Renderer Built Successfully.");
    if (static_cast<bool>(conf["SmartMode"]) == true)
        this->renderer->SmartModeInit(*this->config);
    this->loadTimeline();
}

void    fender::Manager::loadTimeline()
{
    this->sceneList = futils::string::split(this->timeline["timeline"]["list"],
                                            ',');
}

void    fender::Manager::start()
{
    futils::Clock   clock;
    float           elapsed;

    if (this->sceneList.empty())
        return ;
    for (auto &sceneName: this->sceneList)
    {
        this->renderer->changeScene(this->timeline.proxy(), sceneName);
        auto scene = this->sceneFactory.build(sceneName);
        if (scene) {
            scene->provideRenderer(*this->renderer);
            scene->init();
            clock.start();
            while (scene->isDone() == false
                   && this->renderer->isRunning()) {
                elapsed = clock.loop();
                clock.start();
                this->renderer->pollEvents();
                scene->update(elapsed);
                if (clock.bufferedElapsedTime() >= 0.016)
                {
                    this->renderer->refresh();
                    clock.resetBuffer();
                }
                clock.end();
            }
        }
    }
}

void    fender::Manager::run()
{

}
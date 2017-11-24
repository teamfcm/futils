//
// Created by ganz on 16/08/17.
//

# include "fender.hpp"
# include "log.hpp"
# include "sfml/SFMLRender.hpp"
# include "ncurses/CursesRender.hpp"
# include "ini.hpp"
# include "clock.hpp"
# include <unistd.h>

extern "C"
fender::Manager *manager(futils::Ini const &config)
{
    return new fender::Manager(config);
}

fender::Manager::Manager(futils::Ini const &config):
        config(configProxy)
{
    this->renderingBuilders["SFML"] = []() {
        return std::make_unique<fender::SFMLRender>();
    };
    this->renderingBuilders["NCURSES"] = []() {
        return std::make_unique<fender::CursesRender>();
    };

    auto global = (*this->config)["global"];
    auto conf = (*this->config)["fender"];
    std::string renderLibrary = global["RenderLibrary"];
    LOUT("Selected RenderLibrary : " + renderLibrary);
    if (!(this->renderer = this->renderingBuilders[renderLibrary]()))
        throw std::runtime_error("Failed To Build " + std::string(global["RenderLibrary"]));
    LOUT("Rendering Built Successfully.");
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
    // TODO: Remove sceneList etc...
    if (this->sceneList.empty())
        return 1;
    return this->run();
}

int fender::Manager::run()
{
    futils::Clock   clock;
    float           elapsed;
    for (auto &sceneName: this->sceneList)
    {
        this->renderer->changeScene(this->timeline.proxy(), sceneName);
        auto scene = this->sceneFactory.build(sceneName);
        if (scene) {
            scene->provideECS(this->renderer->getECS());
            scene->provideRenderer(*this->renderer);
            scene->init();
            clock.start();
            while (scene->isDone() == false && this->renderer->isRunning())
            {
                elapsed = clock.loop();
                clock.start();
                this->renderer->pollEvents();
                scene->update(elapsed);
                this->renderer->update(elapsed);
                clock.end();
            }
        }
    }
    return status;
}
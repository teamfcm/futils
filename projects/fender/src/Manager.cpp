//
// Created by ganz on 16/08/17.
//

# include <unistd.h>
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
    this->loadTimeline();
}

void    fender::Manager::loadTimeline()
{

}

int fender::Manager::start()
{
    // Used for initialization from client ?
    return 0;
}

int fender::Manager::run()
{
    futils::Clock   clock;
    float           elapsed;
    (void)elapsed;
    (void)clock;
//    for (auto &sceneName: this->sceneList)
//    {
//        this->renderer->changeScene(this->timeline.proxy(), sceneName);
//        auto scene = this->sceneFactory.build(sceneName);
//        if (scene) {
//            scene->provideECS(this->renderer->getECS());
//            scene->provideRenderer(*this->renderer);
//            scene->init();
//            clock.start();
//            while (scene->isDone() == false && this->renderer->isRunning())
//            {
//                elapsed = clock.loop();
//                clock.start();
//                this->renderer->pollEvents();
//                scene->update(elapsed);
//                this->renderer->update(elapsed);
//                clock.end();
//            }
//        }
//    }
    return status;
}
//
// Created by ganz on 19/08/17.
//

# include "Splashscreen.hpp"
# include "fender.hpp"
#include "../lib/fender/release/fender.hpp"

demo::scenes::Splashscreen::Splashscreen(demo::Demo &e,
                                         std::string const &sceneFolder):
        env(e),
        layout(sceneFolder + "Splashscreen.ini")
{
    this->name = "Splashscreen";
    layout.rename("Splashscreen");
    this->eventSystem.setRole(fender::MediatorRole::Client);
    auto    &leaveScene = *this->eventSystem.createInputEvent("QuitSplashscreen");
    leaveScene.addKey(fender::Input::Escape, fender::State::GoingDown);
    leaveScene.isReady = [this](){
        auto &bar = this->layout.get<fender::Bar>("loadingBar");
        return (bar.getCurrent() >= bar.getMaximum());
    };
    leaveScene.start = [this](){
        this->done = true;
    };
    auto    &decreaseBar = *this->eventSystem.createInputEvent("DecreaseBar");
    decreaseBar.addKey(fender::Input::Space, fender::State::GoingDown);
    decreaseBar.isReady = [this](){
        auto &bar = this->layout.get<fender::Bar>("loadingBar");
        return (bar.getCurrent() < bar.getMaximum());
    };
    decreaseBar.start = [this](){
        auto &bar = this->layout.get<fender::Bar>("loadingBar");
        bar.increment(-10);
    };
}

void    demo::scenes::Splashscreen::init()
{
    this->renderer->openWindow();
    this->renderer->registerLayout(this->layout);
    this->renderer->useLayout("Splashscreen");
    auto logo = this->layout.get<fender::AnimatedImage>("logo");
    auto loadingBar = this->layout.get<fender::Bar>("loadingBar");
//    auto popup = this->layout.get<fender::Popup>("popup");
//    auto button = this->layout.get<fender::Button>("exit");
//    button.onClick = [this](){
//        this->done = true;
//    };
    this->layout.setVisible(true);
}

void    demo::scenes::Splashscreen::update()
{
    auto &loadingBar = this->layout.get<fender::Bar>("loadingBar");
    if (loadingBar.done())
    {
        loadingBar.setLabel("Press Any Key");
    }
    else
    {
        loadingBar.setLabel(" Loading (" + std::to_string(static_cast<int>(loadingBar.getCurrent())) + " %)");
        loadingBar.increment(0.5);
    }
}
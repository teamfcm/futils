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
    leaveScene.addKey(fender::Input::Escape);
    leaveScene.start = [this](){
        this->done = true;
    };
}

void    demo::scenes::Splashscreen::init()
{
    this->renderer->openWindow();
    this->renderer->registerLayout(this->layout);
    this->renderer->useLayout("Splashscreen");
    auto logo = this->layout.get<fender::AnimatedImage>("logo");
    auto loadingBar = this->layout.get<fender::Bar>("loadingBar");
    auto popup = this->layout.get<fender::Popup>("popup");
    auto button = this->layout.get<fender::Button>("exit");
    button.onClick = [this](){
        this->done = true;
    };
    this->layout.setVisible(true);
    fender::InputEvent  fillProgressBar(fender::Input::Space);
//    This way, if Event->IsReady() returns false, we still keep the event for
//    several frames, and we'll try again each time
//    Until the event dies and we remove it from the system
    fillProgressBar.setLifespan(10);
    fillProgressBar.start = [this](){
        auto &loadingBar = this->layout.get<fender::Bar>("loadingBar");
        loadingBar.increment();
    };
}

void    demo::scenes::Splashscreen::update()
{
    auto &loadingBar = this->layout.get<fender::Bar>("loadingBar");
    if (loadingBar.done())
    {
        loadingBar.setLabel("Press Enter to Quit");
    }
    else
    {
        loadingBar.setLabel(" (" + std::to_string(loadingBar.getCurrent()) + " %)");
        loadingBar.increment();
    }
}
//
// Created by ganz on 19/08/17.
//

# include "Splashscreen.hpp"

demo::scenes::Splashscreen::Splashscreen(demo::Demo &e,
                                         std::string const &sceneFolder):
        env(e),
        layout(sceneFolder + "Splashscreen.ini")
{
    this->name = "Splashscreen";
    layout.rename("Splashscreen");
    this->eventSystem.setRole(fender::MediatorRole::Client);
    auto &version = this->layout.get<fender::Message>("version");
    version.setContent("fender version 1.0");
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
        return (bar.getCurrent() < bar.getMaximum() && !bar.barIsVisible());
    };
    decreaseBar.start = [this](){
        auto &bar = this->layout.get<fender::Bar>("loadingBar");
        bar.increment(-10);
    };
    auto &tmpBarController = *this->eventSystem.createInputEvent("TmpBar");
    tmpBarController.addKey(fender::Input::Q, fender::State::GoingDown);
    tmpBarController.start = [this](){
        auto &tmpBar = this->layout.get<fender::Bar>("tmpBar");
        tmpBar.increment(1);
    };
}

void    demo::scenes::Splashscreen::init()
{
    this->renderer->openWindow();
    this->renderer->registerLayout(this->layout);
    this->renderer->useLayout("Splashscreen");
    auto logo = this->layout.get<fender::AnimatedImage>("logo");
    logo.setAlpha(0);
    auto loadingBar = this->layout.get<fender::Bar>("loadingBar");
//    auto popup = this->layout.get<fender::Popup>("popup");
//    auto button = this->layout.get<fender::Button>("exit");
//    button.onClick = [this](){
//        this->done = true;
//    };
    this->layout.setVisible(true);
}

void    demo::scenes::Splashscreen::update(float elapsed)
{
    auto &loadingBar = this->layout.get<fender::Bar>("loadingBar");
    auto &logo = this->layout.get<fender::AnimatedImage>("logo");
    
    futils::FloatingRange<double>   incrementRange(20, 40);
    loadingBar.showBar();
    if (loadingBar.done())
    {
        loadingBar.setLabel("Press the escape key");
        loadingBar.hideBar();
    }
    else
    {
        int currentFloor = static_cast<int>(loadingBar.getCurrent());
        loadingBar.setLabel(" Loading (" + std::to_string(currentFloor) + "."
                            + std::to_string(static_cast<int>((loadingBar.getCurrent() - currentFloor) * 100))
                            + " %)");
        loadingBar.increment(elapsed * incrementRange.getRandom());
        logo.setAlpha(currentFloor * 2.5);
    }
}
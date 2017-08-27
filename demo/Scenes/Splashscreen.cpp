//
// Created by ganz on 19/08/17.
//

# include "Splashscreen.hpp"
#include "../lib/fender/release/fender.h"

demo::scenes::Splashscreen::Splashscreen(demo::Demo &e,
                                         std::string const &sceneFolder):
        env(e),
        layout(sceneFolder + "Splashscreen.ini")
{
    this->name = "Splashscreen";
    layout.rename("Splashscreen");
}

void    demo::scenes::Splashscreen::init()
{
    this->renderer->openWindow();
//    register layout will just make it known to the renderer
    this->renderer->registerLayout(this->layout);
//    if you want to use it, you need to say it !
    this->renderer->useLayout("Splashscreen");
    auto logo = this->layout.get<fender::AnimatedImage>("logo");
    auto loadingBar = this->layout.get<fender::Bar>("loadingBar");
    auto popup = this->layout.get<fender::Popup>("popup");
    auto button = this->layout.get<fender::Button>("exit");
    button.onClick = [this](){
        this->done = true;
    };
    this->layout.setVisible(true);
}

void    demo::scenes::Splashscreen::update()
{
    auto &loadingBar = this->layout.get<fender::Bar>("loadingBar");
    loadingBar.increment(rand() % 4);
    if (loadingBar.done())
        this->done = true;
}
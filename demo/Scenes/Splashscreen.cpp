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
//    this->layout = this->renderer->createLayout();
//    this->layout = this->renderer->loadLayout(this->name);
//    this->layout.load(this->layoutFilePath);
//    auto progressBar = this->layout.get("progressBar");
//    progressBar.onHover([progressBar](){
//        progressBar.displayProgress = true;
//    });
//    progressBar.onLeave([progressBar](){
//        progressBar.displayProgress = false;
//    });
//    progressBar.callback([this, progressBar](){
//        static futils::StringList   assets(this->config["global"]["AssetsList"]);
//        std::string     asset = assets.getAndRemove();
//        this->renderer->loadTexture(asset);
//        progressBar.status = "Loading " + asset;
//        progressBar.advance();
//        )};
}

void    demo::scenes::Splashscreen::update()
{

}
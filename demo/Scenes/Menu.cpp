//
// Create by Felix Ganz
//

# include "Menu.hpp"

demo::scenes::Menu::Menu(demo::Demo &e,
                                         std::string const &sceneFolder):
        env(e),
        layout(sceneFolder + "Menu.ini")
{
    this->name = "Menu";
    layout.rename("Menu");
    this->eventSystem.setRole(fender::MediatorRole::Client);
    auto    &leaveScene = *this->eventSystem.createInputEvent("QuitMenu");
    leaveScene.addKey(fender::Input::Escape, fender::State::GoingDown);
    leaveScene.start = [this](){
        this->done = true;
    };
}

void    demo::scenes::Menu::init()
{
//    this->renderer->registerLayout(this->layout);
//    this->renderer->useLayout("Menu");
//    auto loadingBar = this->layout.get<fender::Bar>("loadingBar");
//    this->layout.setVisible(true);
}

void    demo::scenes::Menu::update()
{
//    auto &loadingBar = this->layout.get<fender::Bar>("loadingBar");
//
//    futils::FloatingRange<double>   incrementRange(0.1, 0.2);
//    loadingBar.showBar();
//    if (loadingBar.done())
//    {
//        loadingBar.setLabel("Press the escape key");
//        loadingBar.hideBar();
//    }
//    else
//    {
//        int currentFloor = static_cast<int>(loadingBar.getCurrent());
//        loadingBar.setLabel(" Loading (" + std::to_string(currentFloor) + "."
//                            + std::to_string(static_cast<int>((loadingBar.getCurrent() - currentFloor) * 100))
//                            + " %)");
//        loadingBar.increment(incrementRange.getRandom());
//    }
}
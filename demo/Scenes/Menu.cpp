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
    auto &popup = this->layout.get<fender::Popup>("QuitPopup");
    popup.hide();
    leaveScene.start = [this](){
        auto &popup = this->layout.get<fender::Popup>("QuitPopup");
        if (popup.isVisible())
        {
            popup.hide();
            this->done = true;
        }
        else
            popup.show();
    };
}

void    demo::scenes::Menu::init()
{
    this->renderer->resize(1600, 900);
    this->renderer->registerLayout(this->layout);
    this->renderer->useLayout("Menu");
    this->layout.setVisible(true);
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
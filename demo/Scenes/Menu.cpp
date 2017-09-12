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
        {
            popup.show();
        }
    };
    auto &quit = this->layout.get<fender::Button>("ZQuitButton");
    quit.onClick = [this](){
        auto &leaveScene = *this->eventSystem.createInputEvent("QuitMenu");
        leaveScene.start();
    };
    quit.onHover = [this](){
        auto &button = this->layout.get<fender::Button>("ZQuitButton");
        button.setAlpha(150);
    };
    quit.onLeave = [this](){
        auto &button = this->layout.get<fender::Button>("ZQuitButton");
        button.setAlpha(255);
    };
}

void    demo::scenes::Menu::init()
{
    this->renderer->openWindow();
    this->renderer->registerLayout(this->layout);
    this->renderer->useLayout("Menu");
    this->layout.setVisible(true);
}

void    demo::scenes::Menu::update(float)
{
}
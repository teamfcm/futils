//
// Create by Felix Ganz
//

# include "Menu.hpp"
#include "../lib/fender/release/fender.hpp"

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
    this->ecs->registerSystem<fender::systems::Ini>();
    
//    Start by making big ass systems and splitting them afterwards.

//    A layout is a set of objects that the fender knows, it will build each as
//    one entity composed with several components.
//    Should not change much about the user.
    
//    Object assembled from scratch. Later on the engine will offer readyToUse objets like this->layout.get<Button>(); or this->ecs->get()...
    auto buttonObject = this->ecs->createEntity<fender::BaseObject>();
    if (buttonObject != nullptr)
    {
//        auto &drawable = buttonObject->attachComponent<fender::components::Drawable>();
//        TODO: If no parent -> uses all drawing space;
//        drawable.setParent(blablou);
//        drawable.setRSize(10, 10);
//        drawable.setPosition(0, 0);
//        drawable.setSize(100, 100);
//          TODO: For getting info from file, maybe have GuiObject be default,
//        and LayoutObject be sourced from INI File.
//        And Game Object could have a component Stored where you'd fetch data using some kind of identifier
//        for example Player or World could be sourced to a ini file given to the constructor ?
        auto &source = buttonObject->attachComponent<fender::components::Ini>("Menu.ini", "Button_0");
        
        auto &drawable = buttonObject->attachComponent<fender::components::Drawable>();
        drawable.setColor(fender::Color::WHITE);
        drawable.setBorder(fender::Color::RED, 5);
        
        auto &position = buttonObject->attachComponent<fender::components::Object2d>();
        position.setRPosition({(float)source["pos"][0], (float)source["pos"][1]});
        position.setRSize({(float)source["size"][0], (float)source["size"][1]});
        
        auto &onHover = buttonObject->attachComponent<fender::components::Hoverable>();
        onHover.setArea(position.getPosition(), position.getSize());
        onHover.onHover = [buttonObject](){
            auto &drawable = static_cast<fender::components::Drawable &>(buttonObject->getComponent("Drawable"));
            drawable.setBorder(fender::Color::MAGENTA, 10);
        };
        onHover.onLeave = [buttonObject](){
            auto &drawable = static_cast<fender::components::Drawable &>(buttonObject->getComponent("Drawable"));
            drawable.setBorder(fender::Color::RED, 5);
        };
        
        auto &onClick = buttonObject->attachComponent<fender::components::Clickable>();
        onClick.setArea(position.getPosition(), position.getSize());
        onClick.setAction([this, buttonObject](){
            auto &src = static_cast<fender::components::Ini &>(buttonObject->getComponent("Ini"));
            src["posX"] = "500";
            auto click = static_cast<fender::components::Clickable *>(&buttonObject->getComponent("Clickable"));
            click->setAction([this](){
                this->done = true;
            });
        });
    }
}

void    demo::scenes::Menu::update(float)
{

}
//
// Create by Felix Ganz
//

# include "Menu.hpp"
# include "fender.hpp"

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
    this->ecs->registerSystem<fender::systems::Animation>();
    this->buttons["Button_0"] = this->ecs->createEntity<demo::Button>("Button_0");
    auto &test = this->buttons["Button_0"];
    test->onClick([this](){
        this->done = true;
    });
    this->buttons["Button_1"] = this->ecs->createEntity<demo::Button>("Button_1");
    auto &test2 = this->buttons["Button_1"];
    test2->onClick([this](){
        this->done = true;
    });
    this->buttons["Button_2"] = this->ecs->createEntity<demo::Button>("Button_2");
    auto &test3 = this->buttons["Button_2"];
    test3->onClick([this](){
        this->done = true;
    });
    this->buttons["Button_3"] = this->ecs->createEntity<demo::Button>("Button_3");
    auto &test4 = this->buttons["Button_3"];
    test4->onClick([this](){
        this->done = true;
    });
    auto &animation = test4->attachComponent<fender::components::Animated>();
    animation.callback = [test4](float elapsed){
        auto &position = static_cast<fender::components::Object2d &>(test4->getComponent("Object2d"));
        if (position.getPosition().Y < 40)
            position.move(0, 100 * elapsed);
        else
        {
            auto &animation = static_cast<fender::components::Animated &>(test4->getComponent("Animated"));
            animation.callback = [test4](float elapsed){
                auto &pos = static_cast<fender::components::Object2d &>(test4->getComponent("Object2d"));
                pos.move(0, -100 * elapsed);
            };
        }
    };
    animation.isDone = [test4](){
        auto &position = static_cast<fender::components::Object2d &>(test4->getComponent("Object2d"));
        return position.getPosition().Y < -250;
    };
////    Object assembled from scratch. Later on the engine will offer readyToUse objets like this->layout.get<Button>(); or this->ecs->get()...
//    auto buttonObject = this->ecs->createEntity<fender::BaseObject>();
//    if (buttonObject != nullptr)
//    {
////        Load Informations from file
//        auto &source = buttonObject->attachComponent<fender::components::Ini>("Menu.ini", "Button_0");
//
////        Set Drawing informations
//        auto &drawable = buttonObject->attachComponent<fender::components::Drawable>();
//        drawable.setColor(fender::Color::WHITE);
//        drawable.setBorder(fender::Color::WHITE, 1);
//
////        Set Position
//        auto &position = buttonObject->attachComponent<fender::components::Object2d>();
//        position.setRPosition({(float)source["pos"][0], (float)source["pos"][1]});
//        position.setRSize({(float)source["size"][0], (float)source["size"][1]});
//
////        SetAction onHover and Leave
//        auto &onHover = buttonObject->attachComponent<fender::components::Hoverable>();
//        onHover.setArea(position.getPosition(), position.getSize());
//        onHover.onHover = [buttonObject](){
//            auto &drawable = static_cast<fender::components::Drawable &>(buttonObject->getComponent("Drawable"));
//            drawable.setBorder(fender::Color::RED, 3);
//        };
//        onHover.onLeave = [buttonObject](){
//            auto &drawable = static_cast<fender::components::Drawable &>(buttonObject->getComponent("Drawable"));
//            drawable.setBorder(fender::Color::WHITE, 1);
//        };
//
////        On Click action
//        auto &onClick = buttonObject->attachComponent<fender::components::Clickable>();
//        onClick.setArea(position.getPosition(), position.getSize());
//        onClick.setAction([this, buttonObject](){
//            auto &src = static_cast<fender::components::Ini &>(buttonObject->getComponent("Ini"));
//            src["posX"] = "500";
//            auto click = static_cast<fender::components::Clickable *>(&buttonObject->getComponent("Clickable"));
//            click->setAction([this](){
//                this->done = true;
//            });
//        });
//    }
}

void    demo::scenes::Menu::update(float)
{

}
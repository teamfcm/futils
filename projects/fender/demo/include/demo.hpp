//
// Created by ganz on 19/08/17.
//

#ifndef DEMO_DEMO_HPP
#define DEMO_DEMO_HPP

# include "App.hpp"

namespace demo
{
    class   Button : public futils::IEntity
    {
        std::string             name;
    public:
        Button(std::string const &name): name(name) {}
        
        void    init()
        {
            //    Object assembled from scratch. Later on the engine will offer readyToUse objets like this->layout.get<Button>(); or this->ecs->get()...
//        Load Informations from file
            auto &source = this->attachComponent<fender::components::Ini>("Menu.ini", name);
            auto &drawable = this->attachComponent<fender::components::Drawable>();
            auto &position = this->attachComponent<fender::components::Object2d>();
            auto &onHover = this->attachComponent<fender::components::Hoverable>();
            auto &clickAction = this->attachComponent<fender::components::Clickable>();
//        Set Drawing informations
            drawable.setColor(fender::Color::WHITE);
            drawable.setBorder(fender::Color::WHITE, 1);

//        Set Position
            position.setRPosition({(float) source["pos"][0], (float) source["pos"][1]});
            position.setRSize({(float) source["size"][0], (float) source["size"][1]});

//        SetAction onHover and Leave
            onHover.setArea(position.getPosition(), position.getSize());
            onHover.onHover = [this]() {
                auto &dr = static_cast<fender::components::Drawable &>(this->getComponent("Drawable"));
                dr.setBorder(fender::Color::RED, 3);
            };
            onHover.onLeave = [this]() {
                auto &dr = static_cast<fender::components::Drawable &>(this->getComponent("Drawable"));
                dr.setBorder(fender::Color::WHITE, 1);
            };

//        On Click action
            clickAction.setArea(position.getPosition(), position.getSize());
            clickAction.setAction([this](){
                std::cout << "No action for button " + this->name << std::endl;
            });
        }
    
        void    onClick(std::function<void(void)> func)
        {
            auto &clickAction = static_cast<fender::components::Clickable &>(this->getComponent("Clickable"));
            clickAction.setAction(func);
        }
    };
}

#endif //DEMO_DEMO_HPP

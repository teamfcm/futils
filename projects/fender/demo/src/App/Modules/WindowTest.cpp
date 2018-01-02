//
// Created by arroganz on 1/1/18.
//

#include "WindowTest.hpp"
#include "inputKeys.hpp"

void WindowTest::run(float) {
    if (window == nullptr) {
        window = &entityManager->create<fender::entities::Window>();
        auto &win = window->get<fender::components::Window>();
        if (win.isOpen)
        {

        } else {
            win.title = "TestWindow";
            win.size.w = 800;
            win.size.h = 600;
            win.position.x = 200;
            win.position.y = 200;
            win.visible = true;

            onEscape = [this](){
                events->send<fender::events::Shutdown>();
                entityManager->removeSystem(name);
            };

            addReaction<futils::Input>([this](futils::IMediatorPacket &pkg){
                auto &input = futils::Mediator::rebuild<futils::Input>(pkg);
                if (input == futils::Input::Escape) {
                    onEscape();
                }
                if (input == futils::Input::Return)
                {
                    onEscape = [this](){
                        entityManager->removeSystem(name);
                    };
                    afterDeath = [](futils::EntityManager *em){
                        em->addSystem<WindowTest>();
                    };
                }
            });
            addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
                entityManager->removeSystem(name);
            });
        }
    }
}
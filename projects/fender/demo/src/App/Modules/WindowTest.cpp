//
// Created by arroganz on 1/1/18.
//

#include "WindowTest.hpp"
#include "inputKeys.hpp"

void WindowTest::initWindow()
{
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

//        addReaction<futils::Keys>([this](futils::IMediatorPacket &pkg){
//           auto &key =  futils::Mediator::rebuild<futils::Keys>(pkg);
//            if (key == futils::Keys::Escape || key == futils::Keys::K)
//                events->send<fender::events::Shutdown>();
//        });
        addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
            entityManager->removeSystem(name);
        });

        camera = &entityManager->create<fender::entities::Camera>();
        auto &cam = camera->get<fender::components::Camera>();
        cam.window = window;
        cam.activated = true;
    }
}

void WindowTest::initInputs()
{
    input = &entityManager->create<fender::entities::Input>();
    auto &component = input->get<fender::components::Input>();
    component.name = "WindowTest";
    component.activated = true;
    futils::InputSequence escape;
    futils::InputAction action(futils::Keys::Escape, futils::InputState::Down);
    escape.actions.push_back(action);
    component.map[escape] = [this](){
        events->send<fender::events::Shutdown>();
    };
}

void WindowTest::run(float) {
    if (window == nullptr) {
        initWindow();
        initInputs();
    }
}
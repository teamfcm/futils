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

    futils::InputSequence quit;
    futils::InputAction action2(futils::Keys::LButton, futils::InputState::Down);
    quit.actions.push_back(action2);

    futils::InputSequence moveup;
    futils::InputAction action3(futils::Keys::MouseWheelUp, futils::InputState::Wheel);
    moveup.actions.push_back(action3);

    futils::InputSequence moveup2;
    futils::InputAction action4(futils::Keys::JoystickB, futils::InputState::Joystick);
    moveup2.actions.push_back(action4);

    component.map[escape] = [this]() {
        events->send<fender::events::Shutdown>();
    };
    component.map[quit] = [this]() {
        events->send<fender::events::Shutdown>();
    };
    component.map[moveup] = [this]() {
        events->send<fender::events::Shutdown>();
    };

    component.map[moveup2] = [this]() {
        events->send<fender::events::Shutdown>();
    };
}

void WindowTest::run(float) {
    if (window == nullptr) {
        initWindow();
        initInputs();
    }
}
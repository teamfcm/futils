//
// Created by arroganz on 12/17/17.
//

#ifndef FENDER_SPLASHSCREEN_HPP
#define FENDER_SPLASHSCREEN_HPP

#include "ecs.hpp"
#include "requests.hpp"
#include "events.hpp"
#include "../Entities/Window.hpp"

namespace fender::systems {
    class SplashScreen : public futils::ISystem {
        // TODO: futils::StateMachine<float> member of fender::systems::AStateMachine
        enum Phase
        {
            Init = 0,
            CreateWindow,
            CreateLayout,
            Loader
        };

        int phase{0};
        void init();
        void requestWindow();
        fender::entities::Window *win;
    public:
        SplashScreen();
        void run(float) final;
    };
}

#endif //FENDER_SPLASHSCREEN_HPP

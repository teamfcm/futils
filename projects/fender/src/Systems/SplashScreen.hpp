//
// Created by arroganz on 12/17/17.
//

#ifndef FENDER_SPLASHSCREEN_HPP
#define FENDER_SPLASHSCREEN_HPP

#include "ecs.hpp"
#include "requests.hpp"
#include "events.hpp"

namespace fender::systems {
    class SplashScreen : public futils::ISystem {
        int phase{0};
        void init();
        void requestWindow();
    public:
        SplashScreen();
        void run(float) final;
    };
}

#endif //FENDER_SPLASHSCREEN_HPP

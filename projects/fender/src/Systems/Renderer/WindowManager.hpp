//
// Created by arroganz on 12/16/17.
//

#ifndef FENDER_WINDOWMANAGER_HPP
#define FENDER_WINDOWMANAGER_HPP

#include "ecs.hpp"
#include "requests.hpp"

namespace fender::systems {
    class WindowManager : public futils::ISystem {
        int phase{0};
        void init();
    public:
        WindowManager();
        void run(float) final;
    };
}

#endif //FENDER_WINDOWMANAGER_HPP

//
// Created by arroganz on 12/16/17.
//

#ifndef FENDER_LOG_HPP
#define FENDER_LOG_HPP

#include <ecs.hpp>

namespace fender::systems {
    class Log : public futils::ISystem {
        int phase{0};

        void init();

    public:
        Log();

        void run(float) final;
    };
}

#endif //FENDER_LOG_HPP

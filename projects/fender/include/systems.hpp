//
// Created by arroganz on 11/27/17.
//

#ifndef FENDER_SYSTEMS_HPP
#define FENDER_SYSTEMS_HPP

# include "fender.hpp"
# include "extras.hpp"

namespace fender::systems
{
    class SplashScreen : public futils::ISystem
    {
        std::unique_ptr<Window> _win;
    public:
        SplashScreen();
        void run(float) final;
    };
}

#endif //FENDER_SYSTEMS_HPP

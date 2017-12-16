//
// Created by arroganz on 11/24/17.
//

#ifndef DEMO_APP_HPP
#define DEMO_APP_HPP

# include "fender.hpp"
# include "goToBinDir.hpp"

namespace demo
{
    class App
    {
        using Engine = fender::Fender;

        std::string execPath;
        futils::UP<Engine> engine;
    public:
        App(int, char *argv[]);
        int start();
        int run();
    };
}

#endif //DEMO_APP_HPP

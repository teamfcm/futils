//
// Created by arroganz on 1/1/18.
//

#ifndef DEMO_WINDOWTEST_HPP
#define DEMO_WINDOWTEST_HPP

# include "fender.hpp"
# include "Entities/Window.hpp"

class WindowTest : public futils::ISystem {
    fender::entities::Window *window{nullptr};
public:
    WindowTest(){
        name = "WindowTest";
        afterDeath = [](futils::EntityManager *em){
            em->addSystem<WindowTest>();
        };
    }
    ~WindowTest() override
    {
        delete window;
    }
    void run(float) override;
};


#endif //DEMO_WINDOWTEST_HPP

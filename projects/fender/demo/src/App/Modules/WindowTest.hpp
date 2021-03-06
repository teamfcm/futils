//
// Created by arroganz on 1/1/18.
//

#ifndef DEMO_WINDOWTEST_HPP
#define DEMO_WINDOWTEST_HPP

# include "fender.hpp"
# include "Entities/Window.hpp"
# include "Entities/Input.hpp"
# include "Entities/Camera.hpp"

class WindowTest : public futils::ISystem {
    fender::entities::Window *window{nullptr};
    fender::entities::Input *input{nullptr};
    fender::entities::Camera *camera{nullptr};

    void initWindow();
    void initInputs();
public:
    WindowTest(){
        name = "WindowTest";
    }
    ~WindowTest() override
    {
        delete window;
    }
    void run(float) override;
};


#endif //DEMO_WINDOWTEST_HPP

//
// Created by ganz on 17/08/17.
//

#ifndef DEMO_FACTORY_HPP
#define DEMO_FACTORY_HPP

# include <functional>
# include <unordered_map>
# include <iostream>
# include "fender.h"

namespace demo
{
    class   Env
    {
    public:
        int x{800};
        int y{600};
        std::string name{"prout"};
    };

    class   Intro : public fender::IScene
    {
        demo::Env   &env;
        bool        done{false};
    public:
        Intro(demo::Env &e): env(e) {}
        ~Intro() {}
        virtual bool    isDone() override { return this->done; }
        virtual void    init() override {
            if (this->renderer != nullptr)
                this->renderer->openWindow(200, 200);
        }
        virtual void    update() override {
            this->renderer->write(0, 0, "Coucou");
        };
    };

    class Factory : public fender::ISceneFactory
    {
        using map = std::unordered_map<std::string, std::function<fender::upScene(void)>>;

        map     buildFunctions;
        Env     env;
    public:
        Factory();
        virtual fender::upScene build(std::string const &name) override;
    };
}


#endif //DEMO_FACTORY_HPP

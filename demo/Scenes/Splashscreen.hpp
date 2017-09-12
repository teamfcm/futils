//
// Created by ganz on 19/08/17.
//

#ifndef DEMO_INTRO_HPP
#define DEMO_INTRO_HPP

# include "fender.hpp"
# include "Demo.hpp"

namespace demo
{
    namespace scenes
    {
        class   Splashscreen : public fender::IScene
        {
            demo::Demo          &env;
            bool                done{false};
            fender::Layout      layout;
        public:
            Splashscreen(demo::Demo &,
                         std::string const &sceneFolder = "Scenes/");
            ~Splashscreen(){this->layout.save();}
            virtual bool    isDone() final { return this->done; }
            virtual void    update(float elapsed = 0.0) final;
            virtual void    init() final;
        };
    }
}

#endif //DEMO_INTRO_HPP

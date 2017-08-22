//
// Created by ganz on 19/08/17.
//

#ifndef DEMO_INTRO_HPP
#define DEMO_INTRO_HPP

# include "fender.h"
# include "Demo.hpp"

namespace demo
{
    namespace scenes
    {
        class   Splashscreen : public fender::IScene
        {
            demo::Demo   &env;
            bool    done{false};
        public:
            Splashscreen(demo::Demo &);
            virtual ~Splashscreen() {};
            virtual bool    isDone() override { return this->done; }
            virtual void    update() override;
            virtual void    init() override;
        };
    }
}

#endif //DEMO_INTRO_HPP

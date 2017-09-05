//
// Created by ganz on 04/09/17.
//

#ifndef DEMO_MENU_HPP
#define DEMO_MENU_HPP

# include "fender.hpp"
# include "Demo.hpp"

namespace demo
{
    namespace scenes
    {
        class   Menu : public fender::IScene
        {
            demo::Demo          &env;
            bool                done{false};
            fender::Layout      layout;
        public:
            Menu(demo::Demo &,
                 std::string const &sceneFolder = "Scenes/");
            ~Menu(){this->layout.save();}
            virtual bool    isDone() override { return this->done; }
            virtual void    update() override;
            virtual void    init() override;
        };
    }
}

#endif //DEMO_MENU_HPP

//
// Created by ganz on 28/07/17.
//

#ifndef FENDER_CURSESRENDER_HPP
#define FENDER_CURSESRENDER_HPP

# include <string>
# include "fender.hpp"

namespace fender
{
    class CursesRender : public IRender
    {
    public:
        CursesRender();
        virtual void    openWindow() final;
        virtual void    closeWindow() final;
        virtual void    write(int x, int y, std::string const &msg) final;
        virtual void    refresh() final;
        virtual void    update(float) final {};
        virtual void    resize(int, int) final {}
        virtual bool    isRunning() final {return false;}
        virtual void    loadCurrentLayout() final {}
        virtual void    pollEvents() final {}
        virtual futils::Vec2d<int>  getMousePosition() final {return futils::Vec2d<int>{};}
        virtual bool                mouseIsGoingDown() final {return false;}
        virtual void    changeScene(futils::INI::INIProxy *config = nullptr, std::string const &scope = "config") final {
            (void)config;
            (void)scope;
        }
    };
}

#endif //FENDER_CURSESRENDER_HPP

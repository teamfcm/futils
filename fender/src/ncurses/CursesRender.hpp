//
// Created by ganz on 28/07/17.
//

#ifndef FENDER_CURSESRENDER_HPP
#define FENDER_CURSESRENDER_HPP

# include <string>
# include "fender.h"

namespace fender
{
    class CursesRender : public IRender
    {
    public:
        CursesRender();
        virtual void    openWindow() override;
        virtual void    closeWindow() override;
        virtual void    write(int x, int y, std::string const &msg) override;
        virtual void    refresh() override;
        virtual void    resize(int x, int y) override {}
        virtual bool    isRunning() override {}
        virtual void    loadCurrentLayout() override {}
    };
}

#endif //FENDER_CURSESRENDER_HPP

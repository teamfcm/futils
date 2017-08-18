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
        CursesRender(std::string const &string);
        virtual void    openWindow(int x, int y) override;
        virtual void    closeWindow() override;
        virtual void    write(int x, int y, std::string const &msg) override;
        virtual void    refresh() override;
    };
}

#endif //FENDER_CURSESRENDER_HPP

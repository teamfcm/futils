//
// Created by ganz on 28/07/17.
//

#ifndef FENDER_SFMLRENDER_HPP
#define FENDER_SFMLRENDER_HPP

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <string>
# include "fender.h"

namespace fender
{
    class SFMLRender : public IRender
    {
        sf::RenderWindow  win;
        sf::Event   events;
    public:
        SFMLRender();
        virtual void    openWindow() override;
        virtual void    closeWindow() override;
        virtual void    write(int x, int y, std::string const &msg) override;
        virtual void    refresh() override;
        virtual void    resize(int x, int y) override;
        virtual bool    isRunning() override;
    };
}

#endif //FENDER_SFMLRENDER_HPP

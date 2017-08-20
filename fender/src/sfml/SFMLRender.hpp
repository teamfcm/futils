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
        sf::Texture texture;
        sf::Sprite  logo;
        sf::RectangleShape  back{sf::Vector2f{250, 10}};
        sf::RectangleShape  prog{sf::Vector2f{0, 10}};
        sf::Texture electricityTexture;
        float       progress{0.0};
    public:
        SFMLRender(std::string const &string);
        virtual void    openWindow() override;
        virtual void    closeWindow() override;
        virtual void    write(int x, int y, std::string const &msg) override;
        virtual void    refresh() override;
        virtual void    resize(int x, int y) override;
        virtual bool    isRunning() override;
    };
}

#endif //FENDER_SFMLRENDER_HPP

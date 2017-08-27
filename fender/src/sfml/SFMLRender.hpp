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
    namespace types
    {
        class BaseElement
        {
        protected:
            sf::RectangleShape  rectangle;
            sf::Text            text;
            sf::Text            label;
        public:
            virtual ~BaseElement() {}
            virtual void    update() {}
            virtual void    init() {}
            virtual void    draw(sf::RenderWindow &win)
            {
                win.draw(this->rectangle);
                win.draw(this->text);
            }
            fender::Element     &src;
            BaseElement(fender::Element &src): src(src)
            {

            }

            sf::RectangleShape &getRectangle() {return this->rectangle;};
            sf::Text &getText() {return this->text;};
            sf::Text &getLabel() {return this->label;};
        };

        class AnimatedImage : public BaseElement
        {
            fender::AnimatedImage   &src;
        public:
            AnimatedImage(fender::AnimatedImage &src):
                    BaseElement(src),
                    src(src)
            {

            }

            virtual void    init() override
            {
                this->rectangle.setOutlineColor(sf::Color::Cyan);
            }

            virtual void    update() override
            {

            }

            virtual void    draw(sf::RenderWindow &win) override
            {
                BaseElement::draw(win);
            }
        };

        class Bar : public BaseElement
        {
            sf::RectangleShape      progress;
        public:
            fender::Bar             &src;
            Bar(fender::Bar &src):
                    BaseElement(src),
                    src(src)
            {

            }

            virtual void    init() override
            {
                progress = this->rectangle;
                progress.setOutlineThickness(0);
                progress.setFillColor(sf::Color{.a = 255, .r = 200, .g = 50, .b = 50});
                text.setFillColor(sf::Color::White);
                progress.setSize(sf::Vector2f(0, this->rectangle.getSize().y));
                progress.setPosition(this->rectangle.getPosition());
            }

            virtual void    update() override
            {
                float   x = this->rectangle.getSize().x;
                float   y = this->rectangle.getSize().y;
                float   ratio = (float)this->src.getCurrent() / (float)this->src.getMaximum();
                if (ratio > 0.8)
                    this->progress.setFillColor(sf::Color::Green);
                else if (ratio > 0.6)
                    this->progress.setFillColor(sf::Color::Blue);
                else if (ratio > 0.4)
                    this->progress.setFillColor(sf::Color::Yellow);
                else if (ratio > 0.2)
                    this->progress.setFillColor(sf::Color::Red);
                ratio *= x;
                this->progress.setSize(sf::Vector2f(ratio, y));
                this->text.setString(this->src.getLabel() + std::to_string(this->src.getCurrent())
                                     + " %");
            }

            virtual void    draw(sf::RenderWindow &win) override
            {
                BaseElement::draw(win);
                win.draw(this->progress);
                win.draw(this->text);
            }
        };

        class Popup : public BaseElement
        {
        public:
            fender::Popup             &src;
            Popup(fender::Popup &src):
                    BaseElement(src),
                    src(src)
            {

            }

            virtual void    init() override
            {
                this->rectangle.setOutlineColor(sf::Color::Magenta);
            }

            virtual void    update() override
            {

            }

            virtual void    draw(sf::RenderWindow &win) override
            {
                BaseElement::draw(win);
            }
        };

        class Button : public BaseElement
        {
        public:
            fender::Button             &src;
            Button(fender::Button &src):
                    BaseElement(src),
                    src(src)
            {

            }

            virtual void    init() override
            {
                this->rectangle.setOutlineColor(sf::Color::Blue);
                this->rectangle.setFillColor(sf::Color::White);
            }

            virtual void    update() override
            {

            }

            virtual void    draw(sf::RenderWindow &win) override
            {
                BaseElement::draw(win);
            }
        };
    }

    class SFMLRender : public IRender
    {
        using upBaseElem = std::unique_ptr<types::BaseElement>;

        std::unordered_map<std::string, std::function<void(fender::Element &)>>  elementFactory;
        std::unordered_map<std::string, sf::Font>                   fonts;
        std::unordered_map<std::string, upBaseElem>                 elements;

        sf::RenderWindow  win;
        sf::Event   events;

        void            initFactory();
        template        <typename ElemType, typename SrcType>
        void            create(SrcType &src)
        {
            auto &elem = *(new ElemType(src));
            auto &rectangle = elem.getRectangle();
            auto &text = elem.getText();
            rectangle.setSize(sf::Vector2f{src.getSize().X * this->_windowSize.X / 100.0,
                                           src.getSize().Y * this->_windowSize.Y / 100.0});
            rectangle.setPosition(src.getPosition().X * this->_windowSize.X / 100.0,
                                  src.getPosition().Y * this->_windowSize.Y / 100.0);
            rectangle.setOutlineColor(sf::Color::White);
            rectangle.setOutlineThickness(4);
            rectangle.setFillColor(sf::Color::Transparent);

            text.setFont(this->fonts["game"]);
            text.setCharacterSize(18);
            text.setFillColor(sf::Color::Red);
            text.setPosition(rectangle.getPosition().x +
                             rectangle.getSize().x / 2.0 -
                             text.getString().getSize() / 3.0 *
                             text.getCharacterSize(),
                             rectangle.getPosition().y +
                             rectangle.getSize().y / 2.0 -
                             text.getCharacterSize() / 2.0);
            elem.init();
            if (this->_editorMode) {
                text.setString(
                        text.getString()
                        + " [" + src.getName() + " (" + src.getType() +
                        ")]");
            }
            this->elements
                    .insert(std::pair<std::string, std::unique_ptr<ElemType>>
                                    (src.getName(), &elem));
        };
    public:
        SFMLRender();
        virtual void    openWindow() override;
        virtual void    closeWindow() override;
        virtual void    write(int x, int y, std::string const &msg) override;
        virtual void    refresh() override;
        virtual void    resize(int x, int y) override;
        virtual bool    isRunning() override;
        virtual void    loadCurrentLayout() override;
    };
}

#endif //FENDER_SFMLRENDER_HPP

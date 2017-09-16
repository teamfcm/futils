//
// Created by ganz on 28/07/17.
//

#ifndef FENDER_SFMLRENDER_HPP
#define FENDER_SFMLRENDER_HPP

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <string>
# include "fender.hpp"

namespace fender
{
    namespace elements
    {
        struct   BaseElement
        {
            sf::RectangleShape  rectangle;
            sf::Text            text;
            sf::Text            label;
        };
        
        struct   Message
        {
            sf::Text                text;
            sf::Text                displayedText;
            int                     currentIndex{0};
        };
        
        struct   AnimatedImage
        {
            sf::Texture             texture;
        };
    
        struct   Button
        {
            sf::Text            label;
            sf::Text            hover;
        };

        struct   Popup
        {
            elements::Message       message;
            sf::RectangleShape      mask;
            sf::Text                title;
            sf::Texture             bgTexture;
            sf::Sprite              bg;
        };
        
        struct   Bar
        {
            sf::RectangleShape      progress;
        };
    }
    
// Layout Objects are independant from each other, allowing for a Popup Object
// to contain a Message Element, two Button Elements and a Progress Bar
    namespace layoutObjects
    {
        class   BaseObject
        {
        protected:
            elements::BaseElement   base;
        public:
            fender::Element         &src;
            BaseObject(fender::Element &src): src(src) {}
            
            virtual ~BaseObject() {}
            virtual void    update() {}
            virtual void    init() {}
            virtual void    drawAll(sf::RenderWindow &win)
            {
                this->drawRect(win);
                this->drawText(win);
            }
            virtual void    drawRect(sf::RenderWindow &win)
            {
                win.draw(this->base.rectangle);
            }
            virtual void    drawText(sf::RenderWindow &win)
            {
                win.draw(this->base.text);
            }
        
            sf::RectangleShape &getRectangle() {return this->base.rectangle;};
            sf::Text &getText() {return this->base.text;};
            sf::Text &getLabel() {return this->base.label;};
        };
    
        class   Message : public BaseObject
        {
            elements::Message   elem;
            fender::Message     &src;
        public:
            Message(fender::Message &src):
                    BaseObject(src),
                    src(src)
            {
                this->base.text.setString(src.getContent());
            }
        
            virtual void    init() final
            {
            
            }
        
            virtual void    update() final
            {
            
            }
        
            virtual void    drawAll(sf::RenderWindow &win) final
            {
                BaseObject::drawAll(win);
            }
        };
    
        class   Button : public BaseObject
        {
            elements::Button            elem;
        public:
            fender::Button             &src;
            Button(fender::Button &src):
                    BaseObject(src),
                    src(src)
            {
                this->base.text.setString(src.getName());
            }
        
            virtual void    init() final
            {
                this->base.rectangle.setOutlineColor(sf::Color::Blue);
                this->base.rectangle.setFillColor(sf::Color::White);
            }
        
            virtual void    update() final
            {
            
            }
        
            virtual void    drawAll(sf::RenderWindow &win) final
            {
                BaseObject::drawAll(win);
            }
        };
    
        class   AnimatedImage : public BaseObject
        {
            elements::AnimatedImage elem;
            fender::AnimatedImage   &src;
        public:
            AnimatedImage(fender::AnimatedImage &src):
                    BaseObject(src),
                    src(src)
            {
                if (!this->elem.texture.loadFromFile(this->src.getFilepath()))
                    this->elem.texture.loadFromFile("assets/images/undefined.jpg");
            }
        
            virtual void    init() final
            {
                this->base.rectangle.setOutlineColor(sf::Color::Cyan);
                this->elem.texture.loadFromFile("assets/images/" + this->src.getFilepath());
                this->base.rectangle.setTexture(&this->elem.texture);
                this->base.rectangle.setFillColor(sf::Color::White);
                this->base.rectangle.setFillColor(sf::Color(255, 255, 255, 0));
            }

//            TODO: Change final for final in leaf elements
            virtual void    update() final
            {
                this->base.rectangle.setFillColor(sf::Color(255, 255, 255, this->src.getAlpha()));
            }
        
            virtual void    drawAll(sf::RenderWindow &win) final
            {
                BaseObject::drawAll(win);
            }
        };
    
        class   Bar : public BaseObject
        {
            elements::Bar           elem;
        public:
            fender::Bar             &src;
            Bar(fender::Bar &src):
                    BaseObject(src),
                    src(src)
            {
            
            }
        
            virtual void    init() final
            {
                this->elem.progress = this->base.rectangle;
                this->elem.progress.setOutlineThickness(0);
                this->elem.progress.setFillColor(sf::Color{.a = 255, .r = 200, .g = 50, .b = 50});
                this->base.text.setFillColor(sf::Color::White);
                this->elem.progress.setSize(sf::Vector2f(0, this->base.rectangle.getSize().y));
                this->elem.progress.setPosition(this->base.rectangle.getPosition());
            }
        
            virtual void    update() final
            {
                float   x = this->base.rectangle.getSize().x;
                float   y = this->base.rectangle.getSize().y;
                float   ratio = (float)this->src.getCurrent() / (float)this->src.getMaximum();
                this->elem.progress.setFillColor(sf::Color{.r = (sf::Uint8)(ratio * 127),
                        .g = (sf::Uint8)(ratio * 255),
                        .b = (sf::Uint8)(ratio * 189)});
                ratio *= x;
                this->elem.progress.setSize(sf::Vector2f(ratio, y));
                this->base.text.setString(this->src.getLabel());
                base.text.setPosition(this->base.rectangle.getPosition().x +
                                 this->base.rectangle.getSize().x / 2.0 -
                                 this->base.text.getString().getSize() / 3.0 *
                                 this->base.text.getCharacterSize(),
                                 this->base.rectangle.getPosition().y +
                                 this->base.rectangle.getSize().y / 2.0 -
                                 this->base.text.getCharacterSize() / 2.0);
            }
        
            virtual void    drawAll(sf::RenderWindow &win) final
            {
                if (this->src.barIsVisible())
                {
                    win.draw(this->elem.progress);
                    BaseObject::drawRect(win);
                }
                win.draw(this->base.text);
            }
        };
    
        class   Popup : public BaseObject
        {
            elements::Popup                 elem;
            std::vector<elements::Button>   choices;
        public:
            fender::Popup       &src;
            Popup(fender::Popup &src):
                    BaseObject(src),
                    src(src)
            {
                this->elem.mask.setPosition(0, 0);
                this->elem.mask.setSize(sf::Vector2f(2000, 2000));
                this->elem.mask.setFillColor(sf::Color(125, 125, 125, 150));
                this->elem.bgTexture.loadFromFile("assets/images/" + src.getBackground());
                this->elem.bg.setTexture(this->elem.bgTexture);
            }
            
            virtual void    init() final
            {
                this->base.rectangle.setOutlineColor(sf::Color::Black);
                this->elem.title = this->base.text;
                this->elem.message.text = this->base.text;
                this->elem.title.setString(this->src.getTitle());
                this->elem.message.text.setString(this->src.getMessage());
                this->elem.title.move(0, - this->base.rectangle.getSize().y / 3);
                this->elem.message.text.move(-this->base.rectangle.getSize().x / 3, 0);
                this->elem.bg.setPosition(this->base.rectangle.getPosition());
                auto local = this->elem.bg.getLocalBounds();
                float scaleX = this->base.rectangle.getSize().x / local.width;
                float scaleY = this->base.rectangle.getSize().y / local.height;
                this->elem.bg.setScale(scaleX, scaleY);
                this->elem.message.displayedText = this->elem.message.text;
                this->elem.message.displayedText.setString(this->elem.message.text.getString()[0]);
                for (auto &choice: this->src.getChoices())
                {
                    (void)choice;
                }
            }
        
            virtual void    update() final
            {
                if (!this->src.isVisible())
                    return ;
                if (this->elem.message.displayedText.getString().getSize() <
                    this->elem.message.text.getString().getSize())
                    this->elem.message.displayedText.setString(this->elem.message.text.getString().substring(0, this->elem.message.currentIndex++));
            }
        
            virtual void    drawAll(sf::RenderWindow &win) final
            {
                win.draw(this->elem.mask);
                BaseObject::drawAll(win);
                win.draw(this->elem.bg);
                win.draw(this->elem.title);
                win.draw(this->elem.message.displayedText);
                for (auto &button: this->choices)
                {
                    //            TODO: Obviously elements should be classes with encapsulation methods such as draw
                    (void)button;
                }
            }
        };
    }
    
    class SFMLRender : public IRender
    {
        using upBaseObj = std::unique_ptr<layoutObjects::BaseObject>;
        using ElementFactory = std::unordered_map<std::string, std::function<void(fender::Element &)>>;
        using FontMap = std::unordered_map<std::string, sf::Font>;
        using ElementMap = std::unordered_map<std::string, upBaseObj>;
        using ElementIndexMap = std::multimap<int, layoutObjects::BaseObject *>;
        using InputMap = std::unordered_map<sf::Keyboard::Key, fender::State>;

        ElementFactory          elementFactory;
        FontMap                 fonts;
        ElementMap              elements;
        ElementIndexMap         indexMap;
        sf::RenderWindow        win;
        InputMap                inputs;
        bool                    _mouseIsGoingDown{false};
        futils::Vec2d<int>      _mousePosition;

        void            initFactory();
        
        template        <typename ElemType, typename SrcType>
        void            create(SrcType &src)
        {
//            TODO: Obviously this function cannot stay that way.
//            TODO: Create utils for centering text, objetcs etc... (probably goes with elements encapsulation)
            auto &elem = *(new ElemType(src));
            auto &rectangle = elem.getRectangle();
            auto &text = elem.getText();
            rectangle.setSize(sf::Vector2f{(float)(src.getSize().X * this->_windowSize.X / 100.0),
                                           (float)(src.getSize().Y * this->_windowSize.Y / 100.0)});
            rectangle.setPosition(src.getPosition().X * this->_windowSize.X / 100.0,
                                  src.getPosition().Y * this->_windowSize.Y / 100.0);
            rectangle.setOutlineColor(sf::Color::White);
            if (this->_editorMode)
                rectangle.setOutlineThickness(4);
            rectangle.setFillColor(sf::Color::Transparent);

            text.setFont(this->fonts[this->_systemFont]);
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
            this->indexMap.insert(std::make_pair(src.getZIndex(), &elem));
        };
        
        fender::Command makeCommand(sf::Event const &);
        void            updateChangingKeys();
        void            resetKeys();
    public:
        SFMLRender();
        virtual void    openWindow() final;
        virtual void    closeWindow() final;
        virtual void    write(int x, int y, std::string const &msg) final;
        virtual void    refresh() final;
        virtual void    update(float elapsed) final;
        virtual void    resize(int x, int y) final;
        virtual bool    isRunning() final;
        virtual void    loadCurrentLayout() final;
        virtual void    pollEvents() final;
        virtual bool    mouseIsGoingDown() final {
            return this->_mouseIsGoingDown;
        }
        virtual futils::Vec2d<int>  getMousePosition() final {
            return this->_mousePosition;
        }
        virtual void    changeScene(futils::INI::INIProxy *config = nullptr,
                                    std::string const &scope = "config") final
        {
            this->currentLayout = nullptr;
            this->elements.clear();
            this->_eventSystem.clear();
            this->indexMap.clear();
            if (config)
            {
                if (this->win.isOpen())
                {
                    this->win.close();
                    this->SmartModeInit(*config, scope);
                    this->openWindow();
                }
                else
                    this->SmartModeInit(*config, scope);
            }
        };
        
        sf::RenderWindow    &getWindow() {
            return this->win;
        }
    };
    
    namespace systems
    {
        class   ClickDetection : public fender::ISystem
        {
            SFMLRender                                      &_renderer;
            std::vector<fender::components::Clickable *>    components;
        public:
            ClickDetection(SFMLRender *renderer): _renderer(*renderer)
            {
                this->__requiredComponents.emplace_back("Clickable");
            }
            
            virtual void        run(float) final {
                if (!this->_renderer.mouseIsGoingDown())
                    return ;
                for (auto &compo: this->components)
                {
                    auto const &pos = this->_renderer.getMousePosition();
                    if (compo->getRect().contains(pos))
                    {
                        auto &func = *compo;
                        return func();
                    }
                }
            }
            
            virtual void        addComponent(IComponent &compo) final {
                auto asClickable = static_cast<fender::components::Clickable *>(&compo);
                this->components.push_back(asClickable);
            }
        };
        class   Renderer: public fender::ISystem
        {
            SFMLRender                                          &_renderer;
            std::vector<fender::components::Drawable *>         components;
            float                                               _fluidStep{0.0};
        public:
            Renderer(SFMLRender *renderer): _renderer(*renderer)
            {
                this->__requiredComponents.emplace_back("Drawable");
                this->__requiredComponents.emplace_back("Object2d");
            }
            
            virtual void        run(float elapsed) final
            {
                this->_fluidStep += elapsed;
                if (_fluidStep < 0.016)
                    return ;
                _fluidStep = 0.0;
                auto &win = this->_renderer.getWindow();
                win.clear(sf::Color::Black);
                sf::RectangleShape  rect;
                for (auto &compo: this->components)
                {
//                    auto &object = compo.getAssociatedComponent("Object2d");
//                    rect.setPosition(object->getPosition().X, object->getPosition().Y);
//                    rect.setFillColor(sf::Color::White);
//                    rect.setSize(sf::Vector2f(object->getSize().X, object->getSize().Y));
                    win.draw(rect);
                }
                win.display();
            }
            
            virtual void        addComponent(IComponent &compo) final {
                auto asDrawable = static_cast<fender::components::Drawable *>(&compo);
                this->components.push_back(asDrawable);
//                auto &rect = this->shapes[&compo];
//                rect.setSize(sf::Vector2f(asDrawable->getSize().X, asDrawable->getSize().Y));
//                rect.setPosition(sf::Vector2f(asDrawable->getPosition().X, asDrawable->getPosition().Y));
//                rect.setFillColor(sf::Color::White);
            }
        };
    }
}

#endif //FENDER_SFMLRENDER_HPP

#ifndef FENDER_LIBRARY_H
#define FENDER_LIBRARY_H

# include <iostream>
# include <string>
# include <memory>
# include <functional>
# include <cxxabi.h>
# include <stack>
# include <map>
# include "types.hpp"
# include "dloader.hpp"
# include "ecs.hpp"
# include "futils.hpp"

// TODO: Don't use preprocessing if its not necessary.
// TODO: REMOVE SetAndSave, INIT, SAVE macros.
// TODO: Also change the fini interface so that you can save tokens or sections specifically.
# define QUOTE(str) #str
# define EXPAND_AND_QUOTE(str) QUOTE(str)
# define SetAndSave(v, vv)  this->v = vv; this->fileObject[EXPAND_AND_QUOTE(v)] = vv;
# define INIT(v)            SetAndSave(v, this->v)
# define SAVE(v, vv)        this->fileObject[EXPAND_AND_QUOTE(v)] = vv;

// Utils forward declarations
namespace futils
{
    class Dloader;
    class Ini;
}

namespace fender
{
    class       IRender;

    enum class  State : int
    {
        Undefined,
        Up,
        Down,
        GoingUp,
        GoingDown,
    };
    enum class  Input : int
    {
        Undefined = 0,
        A = 1, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        ArrowUp, ArrowDown, ArrowLeft, ArrowRight,
        Return, Backspace, Space, Escape, Delete, Tab,
        LCtrl, RCtrl, LShift, RShift, Alt,
        Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0,
        Capslock, PageUp, PageDown,
        Ampersand, Hashtag, Quote, DoubleQuote, Dash, Underscore,
        LParenthesis, RParenthesis, LBracket, RBracket, LSquareBracket, RSquareBracket,
        Colon, SemiColon, QuestionMark, ExclamationMark, Comma, Dot, Percent, Asterisk,
        Slash, BackSlash,
        LButton, RButton, MouseWheelUp, MouseWheelDown, MouseWheelButton,
        NBR_SUPPORTED_KEYS
    };
    enum Color : int
    {
        WHITE = 0,
        BLACK,
        RED,
        BLUE,
        CYAN,
        MAGENTA,
        YELLOW,
        TRANSPARENT
    };

    struct      Command
    {
        Input   key{Input::Undefined};
        State   state{State::GoingDown};
        bool    operator == (Command const &other)
        {
            return other.key == this->key && other.state == this->state;
        }
    };
    struct      Border
    {
        int             width{0};
        fender::Color   color{fender::Color::WHITE};
    };
    class       Event
    {
    protected:
        std::string                 _label{""};
        int                         _lifespan{1};
    public:
        virtual ~Event() {}
        
        std::string getLabel() const {return this->_label;}
        void        setLabel(std::string const &label) {this->_label = label;}
        void        setLifespan(int lifespan) { this->_lifespan = lifespan; }
        int         getLifespan() const { return this->_lifespan; }

//        Can the event start ?
        std::function<bool(void)>   isReady{[](){return true;}};
//        Trigger the event
        std::function<void(void)>   start{[](){}};
//        If isReady() failse, onFailure is called
        std::function<void(void)>   onFailure{[](){}};
//        If the event dies without ever being started, call onDeath()
        std::function<void(void)>   onDeath{[](){}};
    };
    enum class  InputEventMode : int
    {
//        As long as the input inputs are in the correct state at the same time in memory
                Simple,
//        If the input inputs are all in the correct state at the same frame - should be rarely used because frame perfection is rare.
                Simultaneous,
//        If the input are set to true sequentially, any error restarts the sequence
                Sequential
    };
    class       InputEvent : public Event
    {
        int                         _identifier{0};
        std::vector<Command>        _inputKeys;
        unsigned int                _matchedKeys{0};
        InputEventMode              _mode{InputEventMode::Simple};
        void                        updateIdentifier()
        {
            std::function<int(int, int)> pairing = [this](int a, int b){
                return (int)((0.5)*(a + b)*(a + b + 1) + b);
            };
            this->_identifier = pairing(static_cast<int>(this->_inputKeys.front().key),
                                        static_cast<int>(this->_inputKeys.front().state));
            if (_inputKeys.size() > 1)
                for (auto mIter = std::next(_inputKeys.begin());
                     mIter != _inputKeys.end(); ++mIter)
                    this->_identifier = pairing(this->_identifier,
                                                pairing(static_cast<int>(mIter->key),
                                                        static_cast<int>(mIter->state)));
            
        };
    public:
//        Hollow ctor for later usage
        InputEvent(std::string const &label)
        {
            this->_label = label;
        }
//        Simple Constructor for single key DOWN InputEvent
        InputEvent(Input key)
        {
            this->_inputKeys.emplace_back(Command{.key = key});
            this->updateIdentifier();
        }
//        Forward of inputs to vector using Initializer List
        InputEvent(std::initializer_list<Command> list): _inputKeys(list)
        {
            this->updateIdentifier();
        }
        
        void        setMode(fender::InputEventMode mode) { this->_mode = mode; }
        int         getIdentifier() const {return this->_identifier;}
        void        setKeyState(Input key, State state) {
            for (auto &command: _inputKeys)
                if (command.key == key)
                {
                    command.state = state;
                    return this->updateIdentifier();
                }
            throw std::runtime_error("In " + std::string(__PRETTY_FUNCTION__) + ":\tInvalid input key");
        }
        
        void        addKey(fender::Input key, fender::State state = fender::State::Down)
        {
            this->_inputKeys.emplace_back(Command{.key = key, .state = state});
        }
        
        void        trigger()
        {
            if (this->isReady())
                this->start();
            else
                this->onFailure();
        }
        
        void                reset()
        {
            this->_matchedKeys = 0;
        }
        
        void                matchInput(Command command)
        {
            for (auto &com: this->_inputKeys)
            {
                if (com == command)
                    this->_matchedKeys++;
            }
            if (this->_matchedKeys == this->_inputKeys.size())
                this->trigger();
        }
    };
    class       LogicalEvent : public Event
    {
    public:
        LogicalEvent(std::string const &label)
        {
            this->_label = label;
        }
    };
    enum class  MediatorRole
    {
        Client,
        Provider
    };
    // TODO: Move Mediator into another hpp
    class IMediatorPacket
    {
    public:
        virtual ~IMediatorPacket() = default;
    };
    // TODO: Review mediator to take not a template but a IMediatorPacket
    template    <typename T>
    class       Mediator
    {
        std::list<T *>      clients;

//        Private constructor for Singleton pattern
        Mediator() {}
    public:
        static Mediator    &get() {
            static auto *inst = new Mediator<T>();
            return *inst;
        };
        
        void        registerClient(T &client)
        {
            this->clients.push_front(&client);
        }
        
        void        unregisterClient(T &client)
        {
            this->clients.remove(&client);
        }
        
        template    <typename MsgType>
        void        send(T &sender, MsgType &msg)
        {
            for (auto &client: this->clients)
            {
                if (client != &sender)
                    client->receive(sender, msg);
            }
        }
    };
    // TODO: Simplify this class, its a bit too complicated.
    class       EventSystem
    {
        using spInputEvent = std::shared_ptr<InputEvent>;
        using spLogicalEvent = std::shared_ptr<LogicalEvent>;
        
        bool                                            paused{false};
        Mediator<EventSystem>                           &_mediator;
        std::unordered_map<std::string, spInputEvent>   _inputEvents;
        std::unordered_map<std::string, spLogicalEvent> _logicalEvents;
        MediatorRole                                    _role;
    public:
        EventSystem():
                _mediator(Mediator<EventSystem>::get())
        {
            _mediator.registerClient(*this);
        }
        ~EventSystem()
        {
            _mediator.unregisterClient(*this);
        }
        
//  Should not be systematically cleared by the manager.
//  Scenes should have the responsibility of clearing events.
        void            clear() {this->_inputEvents.clear();}
        void            pause(){this->paused = true;}
        void            unpause(){this->paused = false;}
        void            setRole(MediatorRole role) { this->_role = role;}
        MediatorRole    getRole() const {return this->_role;}
        
        void            receive(EventSystem &, spInputEvent event)
        {
            this->_inputEvents[event->getLabel()] = event;
        }
        
        void            receive(EventSystem &, spLogicalEvent event)
        {
            this->_logicalEvents[event->getLabel()] = event;
        }
        
        spInputEvent    createInputEvent(std::string const &name)
        {
            if (this->_role == MediatorRole::Provider)
                return nullptr;
            if (this->_inputEvents.find(name) != this->_inputEvents.end())
                return this->_inputEvents.at(name);
            this->_inputEvents[name] = std::make_shared<InputEvent>(name);
            this->_mediator.send<spInputEvent>(*this, this->_inputEvents.at(name));
            return this->_inputEvents.at(name);
        }
        spLogicalEvent  createLogicalEvent(std::string const &name)
        {
            if (this->_role == MediatorRole::Provider)
                return nullptr;
            if (this->_logicalEvents.find(name) != this->_logicalEvents.end())
                return this->_logicalEvents.at(name);
            this->_logicalEvents[name] = std::make_shared<LogicalEvent>(name);
            this->_mediator.send<spLogicalEvent>(*this, this->_logicalEvents.at(name));
            return this->_logicalEvents.at(name);
        }
        std::unordered_map<std::string, spInputEvent>   &getInputEvents()
        {
            return this->_inputEvents;
        };
        std::unordered_map<std::string, spLogicalEvent> &getLogicalEvents()
        {
            return this->_logicalEvents;
        };
    };

    namespace components
    {
        class Windowed : public futils::IComponent
        {
            std::string _name;
            int _width;
            int _height;
        public:
            Windowed(std::string const &name,
                     int width, int height):
                    _name(name),
                    _width(width), _height(height) {
                __name = "Windowed";
            }
            bool isOpen{false};
            void rename(std::string const &name) {
                _name = name;
            }
            void setSize(int x, int y) {
                _width = x;
                _height = y;
            }
        };

        class Runnable : public futils::IComponent
        {
            futils::Action _action;
        public:
            Runnable(futils::Action action): _action(action)
            {

            }

            void run() {
                _action();
            }
        };
        class Sequenced : public futils::IComponent
        {
        public:
            Sequenced() = default;
        };
        class Named : public futils::IComponent
        {
            std::string _name{"UndefinedName"};
        public:
            Named(std::string const &name): _name(name) {

            }

            std::string const &get() const {
                return _name;
            }

            void rename(std::string const &name) {
                _name = name;
            }
        };
        class       Object2d  : public futils::IComponent
        {
        protected:
            futils::Vec2d<float>      position;
            futils::Vec2d<float>      size;
            Object2d                  *parent{nullptr};
        public:
            Object2d(futils::Vec2d<float> const &position = {},
                     futils::Vec2d<float> const &size = {}):
                    position(position), size(size)
            {
                this->__name = "Object2d";
            }
    
            void    setPosition(futils::Vec2d<float> const &pos);
            void    setSize(futils::Vec2d<float> const &size);
            void    setRPosition(futils::Vec2d<float> const &pos);
            void    setRSize(futils::Vec2d<float> const &size);
            futils::Vec2d<float>    getPosition() const {return position;}
            futils::Vec2d<float>    getSize() const {return size;}
            void    move(float x, float y)
            {
                this->position.X += x;
                this->position.Y += y;
            }
        };
        class       Object3d  : public futils::IComponent
        {
        protected:
            futils::Vec3d<float>      position;
            futils::Vec3d<float>      size;
            Object3d                  *parent{nullptr};
        public:
            Object3d(futils::Vec3d<float> const &position = {},
                     futils::Vec3d<float> const &size = {}):
                    position(position), size(size)
            {
                this->__name = "Object3d";
            }
            void    setPosition(futils::Vec3d<float> const &pos)
            {this->position=pos;}
            void    setSize(futils::Vec3d<float> const &size)
            {this->size = size;}
            futils::Vec3d<float>    getPosition() const {return position;}
            futils::Vec3d<float>    getSize() const {return size;}
        };
        class       Drawable    : public futils::IComponent
        {
            fender::Color       color{fender::Color::WHITE};
            fender::Border      border;
        public:
            Drawable()
            {
                this->__name = "Drawable";
            }
            void                setColor(fender::Color c){this->color = c;}
            fender::Color       getColor() const {return this->color;}
            void                setBorder(fender::Color c, int width)
            {
                this->border.color = c;
                this->border.width = width;
            }
            Border              getBorder() const {return this->border;}
        };
        class       Clickable   : public futils::IComponent
        {
            futils::Rect<float>           area;
            std::function<void(void)>   function;
        public:
            Clickable()
            {
                this->__name = "Clickable";
            }
        
            void        setArea(float x, float y, float w, float h)
            {
                this->area.X = x;
                this->area.Y = y;
                this->area.EndX = x + w;
                this->area.EndY = y + h;
            }
            void        setArea(futils::Vec2d<float>  const &pos,
                                futils::Vec2d<float> const &size)
            {
                this->area = futils::Rect<float>(pos, size);
            }
            void        setArea(futils::Rect<float> const &ref){this->area = ref;}
            void        setAction(std::function<void(void)> func)
            {
                this->function = func;
            }
            futils::Rect<float> const &getRect() const {return this->area;}
            void        operator () ()
            {
                return this->function();
            }
        };
        class       Hoverable   : public futils::IComponent
        {
            futils::Rect<float>             area;
        public:
            std::function<void(void)>       onHover{[](){}};
            std::function<void(void)>       onLeave{[](){}};
            Hoverable()
            {
                this->__name = "Hoverable";
            }
        
            void        setArea(float x, float y, float w, float h)
            {
                this->area.X = x;
                this->area.Y = y;
                this->area.EndX = x + w;
                this->area.EndY = y + h;
            }
            void        setArea(futils::Vec2d<float>  const &pos,
                                futils::Vec2d<float> const &size)
            {
                this->area = futils::Rect<float>(pos, size);
            }
            void        setArea(futils::Rect<float> const &ref){this->area = ref;}
            futils::Rect<float> const &getRect() const {return this->area;}
        };
        class       Ini   : public futils::IComponent
        {
            std::string     file{""};
            std::string     scope{""};
            std::string     identifier{"id:_" + file + "-" + scope};
            bool            isNew{true};
            bool            hasChanged{false};
            futils::Ini     source{file};
        public:
            Ini(std::string const &file, std::string const &scope): file(file), scope(scope)
            {
                this->__name = "Ini";
            }
    
            std::string const &getIdentifier() const
            {
                return this->identifier;
            }
            
            bool        shouldSave()
            {
                return this->source.hasChanged();
            }
    
            bool        isLoaded()
            {
                return !this->isNew;
            }
            
            futils::INI::Token  &operator [] (std::string const &name)
            {
                this->hasChanged = true;
                return source[this->scope][name];
            }
            
            void                save()
            {
                source.save();
                this->hasChanged = false;
            }
        };
        class       Draggable : public futils::IComponent
        {
            bool    followingMouse{false};
        public:
            Draggable() {this->__name = "Draggable";}
            bool         isDragged() const {return this->followingMouse;}
        };
        class       Animated : public futils::IComponent
        {
        public:
            Animated() {this->__name = "Animated";}
            std::function<void(float)>   callback{[](float){}};
            std::function<bool(void)>   isDone{[](){return true;}};
        };
    }
    
    namespace systems
    {
        class WindowManager : public futils::ISystem
        {
            using Renderer = std::unique_ptr<fender::IRender>;
            using builder = std::function<Renderer(void)>;
            std::unordered_map<std::string, builder> renderingBuilders;
            Renderer renderer;
        public:
            WindowManager();
            void run(float) final;
            void openWindow(components::Windowed &);
        };
        class   Ini : public futils::ISystem
        {
            std::unordered_map<std::string, components::Ini *>    sources;
        public:
            Ini() = default;
            virtual void    run(float)
            {

            }
            
            void            loadSource(components::Ini &source)
            {
                (void)source;
            }
            
            void            saveSource(components::Ini &source)
            {
                source.save();
            }
        };
        class   DragAndDrop : public futils::ISystem
        {
        public:
            DragAndDrop() = default;
            
            void    run(float) override
            {

            }
        };
        class   Animation : public futils::ISystem
        {
        public:
            Animation() = default;
            virtual void    run(float)
            {

            }
        };
    }

    enum class  WindowStyle
    {
        BORDERLESS,
        NORMAL,
        FULLSCREEN
    };

    enum class  Align
    {
        LEFT,
        CENTER,
        RIGHT,
        TOP,
        BOTTOM
    };
    
    class       Element
    {
    protected:
        futils::INI::Section    &fileObject;
        const std::string       name;
        std::string             type;
        bool                    visible{true};
        futils::Vec2d<int>      position{0, 0};
        futils::Vec2d<int>      size{100, 100};
        int                     alpha{255};
        int                     zIndex{0};

    public:
        Element(futils::INI::Section &sec): fileObject(sec), name(sec.name)
        {
            try
            {
                // LOAD(position.X, int)
                // LOAD(position.Y, int)
                // LOAD(size.X, int)
                // LOAD(size.Y, int)
                // LOAD(visible, bool)
                // LOAD(zIndex, int)
            }
            catch (std::exception const &error)
            {
                SAVE(position.X, position.X)
                SAVE(position.Y, position.Y)
                SAVE(size.X, size.X)
                SAVE(size.Y, size.Y)
                SAVE(visible, visible)
                SAVE(zIndex, zIndex)
                LERR("An error occured while loading Element " + name + ":\t" + error.what());
            }
        }
        virtual ~Element() {}
        
        bool    isVisible() const {return this->visible;}
        void    show(){SetAndSave(visible, true)}
        void    hide(){SetAndSave(visible, false)}
        void    setZIndex(int index) {
            this->zIndex = index;
        }
        int     getZIndex() const {return this->zIndex;}
        const std::string &getName() const {return name;}
        const std::string &getType() const {return type;}
        void setType(const std::string &str) {SetAndSave(type, str)}
        const futils::Vec2d<int> &getPosition() const {return position;}
        void setPosition(const futils::Vec2d<int> &pos) {
            SetAndSave(position.X, pos.X);
            SetAndSave(position.Y, pos.Y);
        }
        const futils::Vec2d<int> &getSize() const {return this->size;}
        void setSize(const futils::Vec2d<int> &vec) {
            SetAndSave(size.X, vec.X);
            SetAndSave(size.Y, vec.Y);
        }
        void                setAlpha(int alpha) {this->alpha = alpha;}
        int                 getAlpha() const {return this->alpha;}
    };
    
    class       Message : public Element
    {
        std::string         font{"Undefined"};
        std::string         content{"Undefined"};
    public:
        Message(futils::INI::Section &sec):
                Element(sec)
        {
            try
            {
                // LOAD(font, std::string)
            }
            catch (std::exception const &error)
            {
                SAVE(font, font);
                LERR("An error occured while loading Text " + name);
            }
        }
        
        void        setFont(std::string const &font)
        {
            this->font = font;
        }
        void        setContent(std::string const &content)
        {
            this->content = content;
        }
        std::string const &getFont() const {return this->font;}
        std::string const &getContent() const {return this->content;}
    };
    
    class       AnimatedImage : public Element
    {
        std::string         filepath{"undefined.jpg"};
        int                 alpha{255};
    public:
        AnimatedImage(futils::INI::Section &sec):
                Element(sec)
        {
            try
            {
                // LOAD(filepath, std::string)
            }
            catch (std::exception const &error)
            {
                SAVE(filepath, filepath)
                LERR("An error occured while loading AnimatedImage " + name);
            }
        }
    
        std::string const   &getFilepath() const {return this->filepath;}
        void                setAlpha(int alpha) {this->alpha = alpha;}
        int                 getAlpha() const {return this->alpha;}
    };

    class       Bar : public Element
    {
        float             minimum{0};
        float             maximum{100};
        float             current{minimum};
        std::string     label{"Undefined"};
        bool            displayLabel{true};
        bool            displayStatus{true};
        bool            visibleBar{true};
    public:
        Bar(futils::INI::Section &sec):
                Element(sec)
        {
            try
            {
                // LOAD(label, std::string)
                // LOAD(displayLabel, bool)
                // LOAD(displayStatus, bool)
            }
            catch (std::exception const &error)
            {
                SAVE(label, label)
                SAVE(displayStatus, displayStatus)
                SAVE(displayLabel, displayLabel)
                LERR("An error occured while loading Bar " + sec.name + ":\t" + error.what());
            }
        }

        void    increment(float add = 1) {
            this->current += add;
            if (this->current < this->minimum)
                this->current = this->minimum;
            if (this->current > this->maximum)
                this->current = this->maximum;
        }
        bool    done() const { return this->current >= this->maximum; }
        std::string const &getLabel() const {return this->label;}
        void    setLabel(std::string const &lab) {this->label = lab;}
        void    setLabelAndSave(std::string const &lab) {SetAndSave(label, lab)}
        float     getMinimum() const {return this->minimum;}
        float     getMaximum() const {return this->maximum;}
        float     getCurrent() const {return this->current;}
        void      hideBar() {this->visibleBar = false;}
        void      showBar() {this->visibleBar = true;}
        bool      barIsVisible() const {return this->visibleBar;}
    };

    class       Popup : public Element
    {
        std::string                 title{"Undefined Popup"};
        std::string                 message{"Error this popup is not initialized."};
        std::string                 background{"Undefined.jpg"};
        std::vector<futils::Choice> choices;
    public:
        Popup(futils::INI::Section &sec):
                Element(sec)
        {
            try
            {
                // LOAD(message, std::string)
                // LOAD(title, std::string)
                // LOAD(background, std::string)
//                for (int i = 0; i < sec["choices"].size(); i++)
//                    this->choices.emplace_back(sec["choices"].get(i));
            }
            catch (std::exception const &error)
            {
//                SAVE(message, message)
//                SAVE(title, title)
                LERR("An error occured while loading Popup " + sec.name + ":\t" + error.what());
            }
        }
        std::string const &getTitle() const {return this->title;}
        std::string const &getMessage() const {return this->message;}
        std::string const &getBackground() const {return this->background;}
        void                addChoice(futils::Choice option)
        {
            this->choices.push_back(option);
        }
        std::vector<std::string>    getChoices() const
        {
            std::vector<std::string>    result;
            
            for (auto &choice: this->choices)
                result.push_back(choice.getLabel());
            return result;
        }
    };

    class       Button : public Element
    {
        std::string                 label{"HoverMe"};
    public:
        std::function<void(void)>   onClick{[](){}};
        std::function<void(void)>   onHover{[](){}};
        std::function<void(void)>   onLeave{[](){}};

        Button(futils::INI::Section &sec):
                Element(sec)
        {
            try
            {
                // LOAD(label, std::string)
            }
            catch (std::exception const &error)
            {
                SAVE(label, label)
                LERR("An error occured while loading Button " + sec.name + ":\t" + error.what());
            }
        }
        
        std::string const &getLabel() const {return this->label;}
    };

    class       Layout
    {
        std::unordered_map<std::string, std::unique_ptr<Element>>    elements;
        futils::Ini                                 ini;
        std::string                                 name{ini.getFilePath()};
        bool                                        visible{true};

        template    <typename ElemType>
        void        create(std::string const &name)
        {
            auto elem = new ElemType(this->ini[name]);
            this->elements
                    .insert(std::pair<std::string, std::unique_ptr<ElemType>>
                                    (name, elem));
            char    *realName = abi::__cxa_demangle(typeid(elem).name(), 0, 0, nullptr);
            std::string typeName(realName);
            typeName.erase(0, 8);
            typeName = typeName.substr(0, typeName.size()-1);
            elem->setType(typeName);
        }

        std::unordered_map<std::string, std::function<void(std::string const &)>> elementFactory;

        void    initFactory()
        {
            elementFactory["AnimatedImage"] = [this](std::string const &name)
            {this->create<fender::AnimatedImage>(name);};
            elementFactory["Bar"] = [this](std::string const &name)
            {this->create<fender::Bar>(name);};
            elementFactory["Popup"] = [this](std::string const &name)
            {this->create<fender::Popup>(name);};
            elementFactory["Button"] = [this](std::string const &name)
            {this->create<fender::Button>(name);};
            elementFactory["Message"] = [this](std::string const &name)
            {this->create<fender::Message>(name);};
        };

    public:
        Layout(std::string const &name):
                ini(name)
        {
            this->initFactory();
            for (auto const &name: this->ini.getScopeList())
            {
                auto type = ini[name]["type"].value.str;
                if (elementFactory.find(type) == elementFactory.end())
                    LERR("You forgot to add a function for creating " + type);
                this->elementFactory[type](name);
            }
        }

        std::unordered_map<std::string, std::unique_ptr<Element>>   const &getElements() const
        {
            return this->elements;
        };

        Element &operator [] (std::string const &name)
        {
            if (this->elements.find(name) == this->elements.end())
                throw std::runtime_error("Cannot create new Layout Element " + name + " . Use get<T> method");
            return *this->elements.at(name);
        }

        template    <typename T>
        T       &get(std::string const &name)
        {
            if (this->elements.find(name) == this->elements.end())
                this->create<T>(name);
            return static_cast<T &>(*this->elements.at(name));
        }

        void    save(std::string const &file = "")
        {
            this->ini.save(file);
        }

        void                rename(std::string const &name) {this->name = name;}
        std::string const &getName() const { return this->name; }
        void                setVisible(bool b) {this->visible = b;}
        bool                isVisible() const { return this->visible; }
    };
    
    class       IRender
    {
    protected:
        using funcMap = std::map<std::string, futils::voidStringFunc>;
    
        std::unordered_map<std::string, fender::Color>  _fenderColors;
        futils::EntityManager   _ecs;
        std::string             _assetsPath;
        std::string             _windowName;
        WindowStyle             _windowStyle;
        bool                    _resizable;
        futils::Vec2d<Align>    _windowAlign;
        funcMap                 configFunctions;
        std::unordered_map<std::string, const fender::Layout *>   knownLayouts;
        const fender::Layout          *currentLayout{nullptr};
        bool                    _editorMode{false};
        fender::EventSystem     _eventSystem;
        std::string             _systemFont{"default"};
        fender::Color           _screenColor;
    public:
        static futils::Vec2d<int>      _windowSize;
        
        virtual ~IRender() {};
        virtual bool    isRunning() = 0;
        virtual void    openWindow() = 0;
        virtual void    closeWindow() = 0;
        virtual void    write(int x, int y, std::string const &) = 0;
//        Used for rendering to the screen if necessary (Not necessary for QT a priori)
        virtual void    refresh() = 0;
        virtual void    resize(int x, int y) = 0;
        virtual void    loadCurrentLayout() = 0;
        virtual void    pollEvents() = 0;
//        Used for updating the ecs systems and other logical updates each Frame
        virtual void    update(float elapsed = 0.0) = 0;
        virtual void    changeScene(futils::Ini *config = nullptr,
                                    std::string const &scope = "fender") = 0;
        virtual futils::Vec2d<int>  getMousePosition() = 0;
        virtual bool                mouseIsGoingDown() = 0;
        fender::Color       getScreenColor() const {return this->_screenColor;}
        void            SmartModeInit(futils::Ini &conf,
                                      std::string const &confScope = "fender");
        void            registerLayout(fender::Layout const &layout)
        {
            this->knownLayouts[layout.getName()] = &layout;
        }
        
        void            useLayout(fender::Layout const &layout)
        {
            this->currentLayout = &layout;
            this->loadCurrentLayout();
        }
        void            useLayout(std::string const &name)
        {
            this->currentLayout = this->knownLayouts.at(name);
            this->loadCurrentLayout();
        }
        
        const futils::Vec2d<int> get_windowSize() const {
            return _windowSize;
        }
        void set_windowSize(const futils::Vec2d<int> &_windowSize) {
            IRender::_windowSize = _windowSize;
        }
        const std::string &get_windowName() const {
            return _windowName;
        }
        void set_windowName(const std::string &_windowName) {
            this->_windowName = _windowName;
        }
        fender::WindowStyle get_windowStyle() const {
            return _windowStyle;
        }
        void    set_windowStyle(fender::WindowStyle _windowStyle) {
            _windowStyle = _windowStyle;
        }
        bool is_resizable() const {
            return _resizable;
        }
        void set_resizable(bool _resizable) {
            _resizable = _resizable;
        }
        const futils::Vec2d<fender::Align> &get_windowAlign() const {
            return _windowAlign;
        }
        void set_windowAlign(const futils::Vec2d<fender::Align> &_windowAlign) {
            this->_windowAlign = _windowAlign;
        }
    };

    class       Manager
    {
        using upRenderer = std::unique_ptr<IRender>;
        using renderBuilder = std::function<upRenderer(void)>;

        upRenderer  renderer;
        futils::Ini &config;
        std::unordered_map<std::string, renderBuilder> renderingBuilders;
        std::unordered_map<std::string, futils::Action> configFunctions;
        int status{0};
        std::string _windowName{"Undefined"};
        futils::EntityManager *entityManager{nullptr};
    public:
        Manager(futils::Ini &config);
        int start();
        int run();

        void    setWindowName(std::string const &name)
        {this->_windowName = name;}
        void provideEntityManager(futils::EntityManager &manager)
        {
            entityManager = &manager;
        }
    };

    class Fender
    {
        futils::UP<futils::Dloader> lib;
        futils::UP<Manager> manager;
        futils::UP<futils::EntityManager> entityManager;
    public:
        Fender(std::string const &);
        int start();
        int run();

        template <typename System, typename ...Args>
        void addSystem(Args ...args) {
            entityManager->addSystem<System>(args...);
        };

        template <typename System>
        void removeSystem() {
            entityManager->removeSystem(futils::demangle<System>());
        }

        template <typename T, typename ...Args>
        T *createEntity(Args ...args) {
            return entityManager->createEntity<T>(args...);
        };
    };
}

#endif
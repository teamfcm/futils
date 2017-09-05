#ifndef FENDER_LIBRARY_H
#define FENDER_LIBRARY_H

# include <iostream>
# include <string>
# include <memory>
# include <functional>
# include <cxxabi.h>
# include <stack>
# include "flog.hpp"
# include "Fini.hpp"
# include "futils.hpp"

# define QUOTE(str) #str
# define EXPAND_AND_QUOTE(str) QUOTE(str)
# define SetAndSave(v, vv)  this->v = vv; this->fileObject[EXPAND_AND_QUOTE(v)] = vv;
# define INIT(v)            SetAndSave(v, this->v)
# define SAVE(v, vv)            this->fileObject[EXPAND_AND_QUOTE(v)] = vv;
# define LOAD(v, type) if (this->fileObject[EXPAND_AND_QUOTE(v)].value == "") \
throw std::runtime_error("Missing argument"); \
this->v = static_cast<type>(this->fileObject[EXPAND_AND_QUOTE(v)]); \

namespace fender
{
    enum class  Color
    {
        WHITE,
        BLACK,
        RED,
        BLUE,
        CYAN,
        MAGENTA,
        YELLOW,
        TRANSPARENT
    };

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
    
    struct      Command
    {
        Input   key{Input::Undefined};
        State   state{State::GoingDown};
        bool    operator == (Command const &other)
        {
            return other.key == this->key && other.state == this->state;
        }
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
//        If the input inputs are all in the correct state at the same frame
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
    
//    Event that doesn't bind to user input but rather logical data change
    class       ConditionalEvent : public Event
    {
        std::function<bool(void)>       _func;
    public:
        ConditionalEvent(std::function<bool(void)> &func): _func(func)
        {
        
        }
    };
    
    enum class  MediatorRole
    {
        Client,
        Provider
    };
    
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
    
    class       EventSystem
    {
        using spInputEvent = std::shared_ptr<InputEvent>;
        bool                                            paused{false};
        Mediator<EventSystem>                           &_mediator;
        std::unordered_map<std::string, spInputEvent>   _events;
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
        
        void            clear() {this->_events.clear();}
        void            pause(){this->paused = true;}
        void            unpause(){this->paused = false;}
        void            setRole(MediatorRole role) { this->_role = role;}
        MediatorRole    getRole() const {return this->_role;}
        
        void            receive(EventSystem &, spInputEvent event)
        {
            this->_events[event->getLabel()] = event;
        }
        
        spInputEvent    createInputEvent(std::string const &name)
        {
            if (this->_role == MediatorRole::Provider)
                return nullptr;
            if (this->_events.find(name) != this->_events.end())
                return this->_events.at(name);
            this->_events[name] = std::make_shared<InputEvent>(name);
            this->_mediator.send<spInputEvent>(*this, this->_events.at(name));
            return this->_events.at(name);
        }
    
        std::unordered_map<std::string, spInputEvent>   &getInputEvents()
        {
            return this->_events;
        };
    };
    
    class       IScene
    {
    protected:
        std::string         name{"Undefined Scene"};
        bool                paused{false};
        IRender             *renderer{nullptr};
        fender::EventSystem eventSystem;
    public:
        virtual ~IScene() {};
        virtual bool    isDone() = 0;
        virtual void    update() = 0;
        virtual void    init() = 0;
    
        void            provideRenderer(IRender &renderer);
        void            pause()
        {
            this->paused = true;
            this->eventSystem.pause();
        }
        void            unpause()
        {
            this->paused = false;
            this->eventSystem.unpause();
        }
    };

    using upScene = std::unique_ptr<IScene>;
    class       ISceneFactory
    {
    public:
        virtual ~ISceneFactory() {};
        virtual upScene build(std::string const &sceneName) = 0;
    };

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
                LOAD(position.X, int)
                LOAD(position.Y, int)
                LOAD(size.X, int)
                LOAD(size.Y, int)
                LOAD(visible, bool)
                LOAD(zIndex, int)
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
                LOAD(font, std::string)
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
                LOAD(filepath, std::string)
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
                LOAD(label, std::string)
                LOAD(displayLabel, bool)
                LOAD(displayStatus, bool)
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
                LOAD(message, std::string)
                LOAD(title, std::string)
                LOAD(background, std::string)
                for (int i = 0; i < sec["choices"].size(); i++)
                    this->choices.emplace_back(sec["choices"].get(i));
            }
            catch (std::exception const &error)
            {
                SAVE(message, message)
                SAVE(title, title)
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

        Button(futils::INI::Section &sec):
                Element(sec)
        {
            try
            {
                LOAD(label, std::string)
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
        futils::INI                                 ini;
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
                auto type = ini[name]["type"].value;
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

        std::string             _assetsPath;
        futils::Vec2d<int>      _windowSize;
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
        
    public:
        virtual ~IRender() {};
        virtual bool    isRunning() = 0;
        virtual void    openWindow() = 0;
        virtual void    closeWindow() = 0;
        virtual void    write(int x, int y, std::string const &) = 0;
        virtual void    refresh() = 0;
        virtual void    resize(int x, int y) = 0;
        virtual void    loadCurrentLayout() = 0;
        virtual void    pollEvents() = 0;
        virtual void    changeScene() = 0;
        
        void            SmartModeInit(futils::INI::INIProxy const &conf,
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
        using upINIProxy = std::unique_ptr<futils::INI::INIProxy>;
        using renderBuilder = std::function<upRenderer(void)>;
        using configFunc = std::function<void(void)>;

        ISceneFactory                   &sceneFactory;
        upRenderer                      renderer;
        upINIProxy                      config;
        futils::INI                     timeline;
        std::unordered_map<std::string, renderBuilder>  renderingBuilders;
        std::unordered_map<std::string, configFunc>     configFunctions;

        std::string                     _windowName{"Undefined"};
        std::vector<std::string>         sceneList;

        void    runConfigBuild();
        void    run();
        void    loadTimeline();
    public:
        Manager(ISceneFactory &fact, futils::INI::INIProxy *config);
        void    start();

        void    setWindowName(std::string const &name)
        {this->_windowName = name;}
    };
}

#endif
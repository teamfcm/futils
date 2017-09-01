#ifndef FENDER_LIBRARY_H
#define FENDER_LIBRARY_H

# include <iostream>
# include <string>
# include <memory>
# include <functional>
# include <cxxabi.h>
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
    enum class Color
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

    class   IRender;

    class   IScene
    {
    protected:
        std::string     name{"Undefined Scene"};
        IRender         *renderer{nullptr};
    public:
        virtual ~IScene() {};
        void            provideRenderer(IRender &renderer);
        virtual bool    isDone() = 0;
        virtual void    update() = 0;
        virtual void    init() = 0;
    };

    using upScene = std::unique_ptr<IScene>;
    class   ISceneFactory
    {
    public:
        virtual ~ISceneFactory() {};
        virtual upScene build(std::string const &sceneName) = 0;
    };

    enum class          WindowStyle
    {
        BORDERLESS,
        NORMAL,
        FULLSCREEN
    };

    enum class          Align
    {
        LEFT,
        CENTER,
        RIGHT,
        TOP,
        BOTTOM
    };


    class   Element
    {
    protected:
        futils::INI::Section    &fileObject;
        const std::string       name;
        std::string             type;
        bool                    visible{true};
        futils::Vec2d<int>      position{0, 0};
        futils::Vec2d<int>      size{100, 100};

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
            }
            catch (std::exception const &error)
            {
                SAVE(position.X, position.X)
                SAVE(position.Y, position.Y)
                SAVE(size.X, size.X)
                SAVE(size.Y, size.Y)
                SAVE(visible, visible)
                LERR("An error occured while loading Element " + name + ":\t" + error.what());
            }
        }
        virtual ~Element() {}

        bool    isVisible() const {return this->visible;}
        void    show(){SetAndSave(visible, true)}
        void    hide(){SetAndSave(visible, false)}
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
    };

    class   AnimatedImage : public Element
    {
        std::string         filepath{"undefined.jpg"};
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
    };

    class   Bar : public Element
    {
        int             minimum{0};
        int             maximum{100};
        int             current{minimum};
        std::string     label{"Undefined"};
        bool            displayLabel{true};
        bool            displayStatus{true};
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

        void    increment(int add = 1) { this->current += add; }
        bool    done() const { return this->current >= this->maximum; }
        std::string const &getLabel() const {return this->label;}
        void    setLabel(std::string const &lab) {this->label = lab;}
        void    setLabelAndSave(std::string const &lab) {SetAndSave(label, lab)}
        int     getMinimum() const {return this->minimum;}
        int     getMaximum() const {return this->maximum;}
        int     getCurrent() const {return this->current;}

    };

    class Popup : public Element
    {
        std::string     title{"Undefined Popup"};
        std::string     message{"Error this popup is not initialized."};
    public:
        Popup(futils::INI::Section &sec):
                Element(sec)
        {
            try
            {
                LOAD(message, std::string)
                LOAD(title, std::string)
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
    };

    class Button : public Element
    {
        std::string                 label{"HoverMe"};
    public:
        std::function<void(void)>   onClick;
        std::function<void(void)>   onHover;

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
    };

    class Layout
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
        };

    public:
        Layout(std::string const &name):
                ini(name)
        {
            this->initFactory();
            for (auto const &name: this->ini.getScopeList())
            {
                auto type = ini[name]["type"].value;
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
    
    enum class State : int
    {
        Undefined = 1,
        Up = 2,
        Down = 4,
        GoingUp = 8,
        GoingDown = 16,
        Starting = 32,
        Occuring = 64,
        Ending = 128,
    };
    
    enum class Keyboard : int
    {
        Undefined = 0,
        A = 1, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        ArrowUp, ArrowDown, ArrowLeft, ArrowRight,
        Return, Backspace, Space, Escape, Delete, Tab, LCtrl, RCtrl, LShift, RShift,
        Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0,
        Capslock, PageUp, PageDown,
        Ampersand, Hashtag, Quote, DoubleQuote, Dash, Underscore,
        LParenthesis, RParenthesis, LBracket, RBracket, LSquareBracket, RSquareBracket,
        Colon, SemiColon, QuestionMark, ExclamationMark, Comma, Dot, Percent, Asterisk,
        Slash, BackSlash,
        NBR_SUPPORTED_KEYBOARD_KEYS
    };
    
    enum class Mouse : int
    {
        Undefined = 0,
        LButton = 1,
        RButton,
        MouseWheelUp,
        MouseWheelDown,
        MouseWheelButton,
        NBR_SUPPORTED_MOUSE_KEYS
    };
    
    class   Event
    {
        std::string                                 _label{""};
        std::vector<std::pair<Keyboard, State>>     _keyboardKeys;
        std::vector<std::pair<Mouse, State>>        _mouseKeys;
        int                                         _identifier{0};
        void                                        updateIdentifier()
        {
            std::function<int(int, int)> pairing = [this](int a, int b){
                return (int)((0.5)*(a + b)*(a + b + 1) + b);
            };
            auto keyboardId = pairing(static_cast<int>(this->_keyboardKeys.front().first),
                                      static_cast<int>(this->_keyboardKeys.front().second));
            if (_keyboardKeys.size() > 1)
                for (auto mIter = std::next(_keyboardKeys.begin());
                     mIter != _keyboardKeys.end(); ++mIter)
                    keyboardId = pairing(keyboardId, pairing(static_cast<int>(mIter->first),
                                                             static_cast<int>(mIter->second)));
            if (this->_mouseKeys.size() == 0)
            {
                this->_identifier = keyboardId;
                return ;
            }
            auto mouseId = pairing(static_cast<int>(this->_mouseKeys.front().first),
                                   static_cast<int>(this->_mouseKeys.front().second));
            if (_mouseKeys.size() > 1)
                for (auto mIter = std::next(_mouseKeys.begin());
                     mIter != _mouseKeys.end(); ++mIter)
                    mouseId = pairing(mouseId, pairing(static_cast<int>(mIter->first),
                                                       static_cast<int>(mIter->second)));
            this->_identifier = pairing(keyboardId, mouseId);
        };
        
    public:
        Event(Mouse key)
        {
            this->_mouseKeys.push_back(std::make_pair(key, fender::State::Down));
            this->updateIdentifier();
        }
        Event(Keyboard key)
        {
            this->_keyboardKeys.push_back(std::make_pair(key, fender::State::Down));
            this->updateIdentifier();
        }
        Event(std::vector<std::pair<Keyboard, State>> const &keyboardVec,
              std::vector<std::pair<Mouse, State>> const &mouseVec = {}):
                _keyboardKeys(keyboardVec),
                _mouseKeys(mouseVec)
        {
            this->updateIdentifier();
        }
        
   
        
        int         getIdentifier() const {return this->_identifier;}
        void        setLabel(std::string const &label) {this->_label = label;}
        std::string getLabel() const {return this->_label;}
    };
    
    template    <typename T>
    class       Mediator
    {
        std::list<T *>      clients;
        
//        Private constructor for Singleton pattern
        Mediator() {}
        
        template        <typename MsgType>
        decltype(auto)  getMap()
        {
            static auto  *map = new std::list<T *>();
            return *map;
        }
    public:
        static Mediator    &get() {
            static auto *inst = new Mediator<T>();
            return *inst;
        };
        
        void        registerClient(T &client)
        {
            this->clients.push_front(&client);
            LOUT("New client registered.");
        }
        
        void        unregisterClient(T &client)
        {
            this->clients.remove(&client);
        }
        
        template    <typename MsgType>
        void        requestMsgType(T &client) {
//            if (this->clients.find(&client) == this->clients.end())
//                throw std::runtime_error("Unregistered clients cannot request Messages.");
            this->getMap<MsgType>().push_back(&client);
        }
        
        template    <typename MsgType>
        void        forgetMsgType(T &client) {
            this->getMap<MsgType>().remove(&client);
        }
        
        template    <typename MsgType>
        void        send(MsgType &msg)
        {
            auto &clients = this->getMap<MsgType>();
            for (auto client : clients)
                client->receive(msg);
        }
    };
    
    class   EventSystem
    {
        Mediator<EventSystem>   &_mediator;
        std::unordered_map<fender::Keyboard, std::function<void(void)>> actions;
        std::unordered_map<int, std::function<void(void)>>     eventFunctions;
        std::unordered_map<int, fender::Event *>          requestedEvents;
    public:
        EventSystem():
                _mediator(Mediator<EventSystem>::get())
        {
            _mediator.registerClient(*this);
        }
        ~EventSystem(){
            _mediator.unregisterClient(*this);
        }
        
        void        emit(fender::Event event)
        {
            _mediator.send<Event>(event);
        }
        
        void        receive(fender::Event &event)
        {
            if (this->eventFunctions.find(event.getIdentifier()) != this->eventFunctions.end())
                this->eventFunctions[event.getIdentifier()]();
        }
        
        void        add(fender::Event &event)
        {
            this->_mediator.requestMsgType<Event>(*this);
            this->requestedEvents[event.getIdentifier()] = &event;
        }
        
        void        add(fender::Event &event, std::function<void(void)> func)
        {
            this->add(event);
            this->eventFunctions[event.getIdentifier()] = func;
        };
    };
    
    class   IRender
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

    class Manager
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

        void    runConfigBuild();
        void    run();
    public:
        Manager(ISceneFactory &fact, futils::INI::INIProxy *config);
        void    start();

        void    setWindowName(std::string const &name)
        {this->_windowName = name;}
    };
}

#endif
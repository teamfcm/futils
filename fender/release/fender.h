#ifndef FENDER_LIBRARY_H
#define FENDER_LIBRARY_H

# include <iostream>
# include <string>
# include <memory>
# include <functional>
# include "Fini.hpp"
# include "futils.hpp"

namespace fender
{
    class   IRender;

    class   IScene
    {
    protected:
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

    class   IRender
    {
    protected:
        using funcMap = std::map<std::string, futils::voidStringFunc>;

        futils::Vec2d<int>      _windowSize;
        std::string             _windowName;
        WindowStyle             _windowStyle;
        bool                    _resizable;
        futils::Vec2d<Align>    _windowAlign;
        funcMap                 configFunctions;
    public:
        virtual ~IRender() {};
        virtual bool    isRunning() = 0;
        virtual void    openWindow() = 0;
        virtual void    closeWindow() = 0;
        virtual void    write(int x, int y, std::string const &) = 0;
        virtual void    refresh() = 0;
        virtual void    resize(int x, int y) = 0;

        void            SmartModeInit(futils::INI::INIProxy const &conf,
                                      std::string const &confScope = "fender");

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
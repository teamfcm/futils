#ifndef FENDER_LIBRARY_H
#define FENDER_LIBRARY_H

# include <iostream>
# include <string>
# include <memory>
# include <functional>
# include "Fini.hpp"

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

    class   IRender
    {
    public:
        virtual ~IRender() {};
        virtual bool    isRunning() = 0;
        virtual void    openWindow() = 0;
        virtual void    closeWindow() = 0;
        virtual void    write(int x, int y, std::string const &) = 0;
        virtual void    refresh() = 0;
        virtual void    resize(int x, int y) = 0;
    };

    class Manager
    {
        using upRenderer = std::unique_ptr<IRender>;
        using upINIProxy = std::unique_ptr<futils::INI::INIProxy>;
        using renderBuilder = std::function<upRenderer(void)>;

        ISceneFactory                   &sceneFactory;
        upRenderer                      renderer;
        upINIProxy                      config;
        futils::INI                     timeline;
        std::unordered_map<std::string, renderBuilder>  renderingBuilders;

        void    runConfigBuild();
        void    run();
    public:
        Manager(ISceneFactory &fact, futils::INI::INIProxy *config);
        void    start();
    };
}

#endif
#ifndef FENDER_LIBRARY_H
#define FENDER_LIBRARY_H

# include <iostream>
# include <string>
# include <memory>

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
        ISceneFactory   &sceneFactory;
        upRenderer      renderer;

        void    run();
    public:
        Manager(ISceneFactory &fact);
        void    loadTimeline(std::string const &);
        void    loadConfig(std::string const &);
        void    start();
    };
}

#endif
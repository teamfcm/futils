#ifndef FENDER_LIBRARY_H
#define FENDER_LIBRARY_H

# include <iostream>
# include <string>
# include <memory>

namespace fender
{
    class   IScene
    {
    public:
        virtual ~IScene() {};
        virtual void    update() = 0;
    };

    using upScene = std::unique_ptr<IScene>;

    class   ISceneFactory
    {
    public:
        virtual ~ISceneFactory() {};
        virtual upScene build(std::string const &sceneName) = 0;
    };

    class Manager
    {
        ISceneFactory   &sceneFactory;

        void    run();
    public:
        Manager(ISceneFactory &fact);
        void    loadTimeline(std::string const &);
        void    loadConfig(std::string const &);
        void    start();
    };

    class   IRender
    {
    public:
        virtual ~IRender() {};
    };
}

#endif
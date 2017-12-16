//
// Created by arroganz on 11/27/17.
//

#ifndef FENDER_SYSTEMS_HPP
#define FENDER_SYSTEMS_HPP

# include "fender.hpp"
# include "extras.hpp"
# include "modules.hpp"
# include "IniManager.hpp"

namespace fender::systems
{
    class Renderer : public futils::ISystem
    {
        futils::UP<IRender> renderer;
        std::unordered_map<std::string, std::function<futils::UP<IRender>(void)>> renderingBuilders;
    public:
        Renderer();
        void run(float) final;
    };
    class SplashScreen : public futils::ISystem
    {
        int phase{0};
        void init();
        void openWindow();
        void changeBackground();
        rutils::IniFile config;
    public:
        SplashScreen();
        void run(float) final;
    };
    class Log : public futils::ISystem
    {
        int phase{0};
        void init();
    public:
        Log();
        void run(float) final;
    };
    // Renderer SubSystems
    class RendererSubSystem : public futils::ISystem
    {
    protected:
        int phase{0};
        futils::Modules modules;
        IRender *renderer;
    public:
        RendererSubSystem();
        virtual void run(float) = 0;
    };
    class WindowManager : public RendererSubSystem
    {
    public:
        WindowManager();
        void run(float) final;
        void openWindow(std::string const &, int, int);
    };
    class Image : public RendererSubSystem
    {
    public:
        Image() = default;
        void run(float) final;
    };
    class Transform : public RendererSubSystem
    {
    public:
        Transform() = default;
        void run(float) final;
    };
}

#endif //FENDER_SYSTEMS_HPP

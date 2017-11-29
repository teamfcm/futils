//
// Created by arroganz on 11/27/17.
//

#ifndef FENDER_SYSTEMS_HPP
#define FENDER_SYSTEMS_HPP

# include "fender.hpp"
# include "extras.hpp"

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
    public:
        SplashScreen();
        void run(float) final;
    };
    class WindowManager : public futils::ISystem
    {
        IRender *renderer{nullptr};
    public:
        WindowManager();
        void run(float) final;
        void openWindow(std::string const &, int, int);
    };
    class   Ini : public futils::ISystem
    {
        std::unordered_map<std::string, components::Ini *>    sources;
    public:
        Ini() {
            name = "Ini";
        };
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
        DragAndDrop() {
            name = "DragAndDrop";
        }

        void    run(float) override
        {

        }
    };
    class   Animation : public futils::ISystem
    {
    public:
        Animation() {
            name = "Animation";
        }
        virtual void    run(float)
        {

        }
    };
}

#endif //FENDER_SYSTEMS_HPP

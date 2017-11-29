//
// Created by arroganz on 11/27/17.
//

# include "fender.hpp"
# include "systems.hpp"

fender::systems::WindowManager::WindowManager()
{
    name = "WindowManager";
}

void fender::systems::WindowManager::openWindow(std::string const &name, int width, int height)
{
    if (!renderer)
        return ;
    renderer->openWindow();
    events::WindowOpened wo;
    wo.name = name;
    wo.width = width;
    wo.height = height;
    events->send(wo);
}

void fender::systems::WindowManager::run(float)
{
    static int i = 0;
    if (i == 0) {
        events->require<events::RendererAccess>(this, [this](futils::IMediatorPacket &pkg){
            auto &rc = static_cast<events::RendererAccess &>(pkg);
            this->renderer = rc.renderer;
            LOUT("Received renderer");
        });
        i++;
    }

    if (renderer == nullptr) {
        requests::GetRenderer gr;
        events->send(gr);
    } else {
        events->require<requests::OpenWindow>(this, [this](futils::IMediatorPacket &pkg) {
            auto &win = static_cast<requests::OpenWindow &>(pkg);
            openWindow(win.name, win.width, win.height);
        });
    }
}
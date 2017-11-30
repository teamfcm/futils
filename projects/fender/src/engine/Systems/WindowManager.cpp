//
// Created by arroganz on 11/27/17.
//

# include "fender.hpp"
# include "systems.hpp"

fender::systems::WindowManager::WindowManager()
{
    name = "WindowManager";
    modules.add("OpenWindow", [this](){
        if (renderer) {
            events->require<requests::OpenWindow>(this, [this](futils::IMediatorPacket &pkg) {
                if (renderer) {
                    auto &win = static_cast<requests::OpenWindow &>(pkg);
                    openWindow(win.name, win.width, win.height);
                    modules.remove("OpenWindow");
                    LOUT("Opening Window");
                }
            });
        }
    });
}

void fender::systems::WindowManager::openWindow(std::string const &name, int width, int height)
{
    // renderer->openWindow();
    events::WindowOpened wo;
    wo.name = name;
    wo.width = width;
    wo.height = height;
    events->send(wo);
}

void fender::systems::WindowManager::run(float)
{
    modules.execute();
}
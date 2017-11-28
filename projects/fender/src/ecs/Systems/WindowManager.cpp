//
// Created by arroganz on 11/27/17.
//

# include "fender.hpp"
# include "CursesRender.hpp"
# include "SFMLRender.hpp"

fender::systems::WindowManager::WindowManager()
{
    futils::Ini config("./config/fender.ini");

    renderingBuilders["SFML"] = []() {
        return std::make_unique<fender::SFMLRender>();
    };
    renderingBuilders["NCURSES"] = []() {
        return std::make_unique<fender::CursesRender>();
    };

    auto global = config["global"];
    auto conf = config["fender"];
    std::string renderLibrary = global["RenderLibrary"];
    LOUT("Selected RenderLibrary : " + renderLibrary);
    if (!(renderer = this->renderingBuilders[renderLibrary]()))
        throw std::runtime_error("Failed To Build " + std::string(global["RenderLibrary"]));
    LOUT("Rendering Built Successfully.");
    if (static_cast<bool>(conf["SmartMode"]) == true)
        this->renderer->SmartModeInit(config);
}

// TODO: Add reaction to packet and add type struct with type_index as typeid(T)
void fender::systems::WindowManager::openWindow(components::Windowed &win)
{
    win.isOpen = true;
    renderer->openWindow();
}

void fender::systems::WindowManager::run(float)
{
    for (auto &window: entityManager->get<components::Windowed>()) {
        if (window->isOpen) {

        } else {
            openWindow(*window);
        }
    }
}
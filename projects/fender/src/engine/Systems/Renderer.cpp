//
// Created by arroganz on 11/29/17.
//

# include "systems.hpp"
# include "SFMLRender.hpp"
# include "CursesRender.hpp"
# include "IniManager.hpp"

fender::systems::Renderer::Renderer() {
//    this->renderingBuilders["SFML"] = []() {
//        return std::make_unique<fender::SFMLRender>();
//    };
//    this->renderingBuilders["NCURSES"] = []() {
//        return std::make_unique<fender::CursesRender>();
//    };
//    rutils::IniFile config("./config/fender.ini");
//    auto global = config["global"];
//    auto conf = config["fender"];
//    std::string renderLibrary = global["RenderLibrary"];
//    LOUT("Selected RenderLibrary : " + renderLibrary);
//    if (!(this->renderer = this->renderingBuilders[renderLibrary]()))
//        throw std::runtime_error("Failed To Build " + std::string(global["RenderLibrary"]));
//    LOUT("Rendering Built Successfully.");
////    if (static_cast<bool>(conf["SmartMode"]) == true)
//  //      this->renderer->SmartModeInit(config);
//    renderer->loadSystems(*entityManager);
}

void fender::systems::Renderer::run(float) {
    //static int i = 0;

    //if (i == 0) {
    //    events->require<requests::GetRenderer>(this, [this](futils::IMediatorPacket &){
    //        events::RendererAccess rc;
    //        rc.renderer = renderer.get();
    //        events->send(rc);
    //    });
    //    events->require<events::WindowOpened>(this, [this](futils::IMediatorPacket &pkg){
    //        auto &wo = static_cast<events::WindowOpened &>(pkg);
    //        (void)wo;
    //    });
    //    i++;
    //}
}
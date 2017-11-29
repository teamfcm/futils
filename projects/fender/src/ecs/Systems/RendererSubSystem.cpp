//
// Created by arroganz on 11/29/17.
//

# include "systems.hpp"

fender::systems::RendererSubSystem::RendererSubSystem() {
    modules.add("GetRenderer", [this](){
        if (this->phase == 0) {
            events->require<events::RendererAccess>(this, [this](futils::IMediatorPacket &pkg){
                auto &rc = static_cast<events::RendererAccess &>(pkg);
                this->renderer = rc.renderer;
                LOUT("Got Renderer");
            });
            phase++;
        }

        if (renderer == nullptr) {
            requests::GetRenderer gr;
            events->send(gr);
        } else {
            LOUT("Removing GetRenderer");
            this->modules.remove("GetRenderer");
        }
    });
}
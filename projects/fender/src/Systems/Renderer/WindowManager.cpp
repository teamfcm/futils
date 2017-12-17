//
// Created by arroganz on 12/16/17.
//

#include <events.hpp>
#include "WindowManager.hpp"

fender::systems::WindowManager::WindowManager()
{

}

void fender::systems::WindowManager::init() {
    phase++;
    events->require<fender::requests::OpenWindow>(this, [this](futils::IMediatorPacket &pkg) {
        auto &w = futils::Mediator::rebuild<fender::requests::OpenWindow>(pkg);
        events->send<std::string>("OpenWindow : "
                                  + std::to_string(w.size.w)
                                  + " "
                                  + std::to_string(w.size.h));
        events::WindowOpened wo;
        wo.size.w = 200;
        wo.size.h = 200;
        wo.pos.x = 0;
        wo.pos.y = 0;
        events->send<events::WindowOpened>(wo);
    });
}

void fender::systems::WindowManager::run(float)
{
    switch (phase) {
        case 0: return init();
    }
}
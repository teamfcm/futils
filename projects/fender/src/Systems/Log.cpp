//
// Created by arroganz on 12/16/17.
//

#include <ini.hpp>
#include "Log.hpp"

fender::systems::Log::Log()
{

}

void fender::systems::Log::init() {
    phase++;
    events->require<std::string>(this, [this](futils::IMediatorPacket &pkg) {
        auto &s = futils::Mediator::rebuild<std::string>(pkg);
        LOUT("LOG => " + s);
    });
}

void fender::systems::Log::run(float)
{
    switch (phase) {
        case 0: return init();
    }
}
//
// Created by arroganz on 1/1/18.
//

#pragma once

# include "fender.hpp"

namespace fender::systems::SFMLSystems
{
    class System : public futils::StateSystem
    {
    protected:
        void shutdown()
        {
            entityManager->removeSystem(name);
        }
        void __init()
        {
            addReaction<events::Shutdown>([this](futils::IMediatorPacket &){
                shutdown();
            });
        }

        System(std::string const &systemName)
        {
            name = systemName;
        }
    public:
        virtual ~System() {}
    };
}

//
// Created by arroganz on 1/1/18.
//

#ifndef FENDER_SYSTEM_HPP
#define FENDER_SYSTEM_HPP

# include "fender.hpp"
# include "ecs.hpp"

namespace fender::systems::SFMLSystems
{
    class System : public futils::StateSystem
    {
    public:
        virtual ~System() {}
    };
}

#endif //FENDER_SYSTEM_HPP

//
// Created by arroganz on 11/29/17.
//

#ifndef FENDER_IRENDER_HPP
#define FENDER_IRENDER_HPP

# include "ecs.hpp"

namespace fender
{
    // Interface
    class IRender
    {
    public:
        virtual ~IRender() {}
// TODO: Simply use the renderer this way !! All you need to do is allow it to add its own systems.
        // This way it will have access to components (abstract) and events.
        virtual void loadSystems(EntityManager &engine);
    };
}

#endif //FENDER_IRENDER_HPP

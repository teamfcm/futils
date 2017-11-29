//
// Created by arroganz on 11/29/17.
//

# include "systems.hpp"

void fender::systems::Transform::run(float)
{
    modules.execute();
}
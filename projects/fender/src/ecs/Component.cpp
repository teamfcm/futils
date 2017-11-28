//
// Created by ganz on 17/09/17.
//

# include "fender.hpp"

void                 futils::IComponent::setEntity(IEntity &ent)
{
    this->__entity = &ent;
}
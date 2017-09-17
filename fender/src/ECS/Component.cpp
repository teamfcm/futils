//
// Created by ganz on 17/09/17.
//

# include "fender.hpp"

fender::IComponent  &fender::IComponent::getAssociatedComponent(std::string const &type)
{
    if (this->__entity == nullptr)
        throw std::runtime_error("No entity is attached to this component of type " + this->__name);
    return this->__entity->getComponent(type);
}

void                 fender::IComponent::setEntity(IEntity &ent)
{
    this->__entity = &ent;
}
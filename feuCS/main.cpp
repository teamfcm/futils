#include <iostream>
#include "feucs.hpp"

class   Component : public futils::IComponent
{
public:
    Component()
    {
        this->__name = "Component";
    }
};

class   System : public futils::ISystem
{
    std::unordered_map<std::string, Component *>    components;
public:
    System() {
        __requiredComponents.emplace_back("Component");
    }
    virtual void    addComponent(futils::IComponent &compo) final
    {
        auto realCompo = dynamic_cast<Component *>(&compo);
        if (realCompo == nullptr)
            throw std::logic_error("You fed me some disgusting component here, pal !");
        this->components[compo.getName()] = realCompo;
    }
    
    virtual void    run() final
    {
    
    }
};

int main() {
    auto em = futils::EntityManager();
    em.registerSystem<System>();
    auto doggy = em.createEntity<futils::GuiObject>();
    doggy->attachComponent<Component>();
    
    while (em.isFine())
        em.run();
    return 0;
}
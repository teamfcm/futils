//
// Created by ganz on 08/09/17.
//

#ifndef FEUCS_FEUCS_HPP
#define FEUCS_FEUCS_HPP

# include <vector>
# include <list>
# include <map>
# include <typeinfo>
# include <functional>
# include <unordered_map>

namespace futils
{
    class   EntityManager;
    
    class   IComponent
    {
    protected:
        std::string __name;
    public:
        virtual ~IComponent() {}
        
        std::string const &getName() const {return this->__name;}
    };
    
    class   ISystem
    {
    protected:
        using StrVec = std::vector<std::string>;
        StrVec          __requiredComponents;
    public:
        virtual ~ISystem() {}
        virtual void          addComponent(IComponent &compo)   = 0;
        virtual void          run()                             = 0;
        StrVec const &getRequiredComponents() const
        {
            return this->__requiredComponents;
        }
    };
    
    class   IEntity
    {
        std::vector<IComponent *>           components;
        std::function<void(IComponent &)>   registerComponentFunction{[](IComponent &){}};
    public:
        virtual ~IEntity() {}
        
        template    <typename Compo, typename ...Args>
        Compo       &attachComponent(Args ...args)
        {
            if (!std::is_base_of<IComponent, Compo>::value)
                throw std::logic_error(std::string(typeid(Compo).name()) + " is not a Component");
            auto compo = new Compo(args...);
            this->components.push_back(compo);
            this->registerComponentFunction(*compo);
            return *compo;
        };
        
        void        setRegisterComponentFunction(std::function<void(IComponent &)> func)
        {
            this->registerComponentFunction = func;
        }
    };
    
    class   GuiObject : public IEntity
    {
    public:
        GuiObject()
        {
        
        }
    };
    
    class   EntityManager
    {
        int                                     status{0};
        std::multimap<std::string, ISystem *>   systemsMap;
        
        int         notifySystems(IComponent &compo)
        {
            int     count{0};
            for (auto it = systemsMap.find(compo.getName()); it != systemsMap.end(); it++)
            {
                auto system = it->second;
                if (system)
                {
                    system->addComponent(compo);
                    count++;
                }
            }
            return count;
        }
    public:
        EntityManager() = default;
        
        template    <typename T, typename ...Args>
        T           *createEntity(Args ...args)
        {
            if (!std::is_base_of<IEntity, T>::value)
                throw std::logic_error(std::string(typeid(T).name()) + " is not an Entity");
            auto ent = new T(args...);
            ent->setRegisterComponentFunction([this](IComponent &compo){
                if (this->notifySystems(compo) == 0)
                    throw std::runtime_error("Idle Component attached to an entity : " + compo.getName());
            });
            return ent;
        }
        
        template    <typename System, typename ...Args>
        void        registerSystem(Args ...args)
        {
            if (!std::is_base_of<ISystem, System>::value)
                throw std::logic_error(std::string(typeid(System).name()) + " is not a System");
            auto system = new System(args...);
            for (auto &handledComponent: system->getRequiredComponents())
            {
                this->systemsMap.insert(std::pair<std::string, ISystem *>(handledComponent, system));
            }
        }
        
        bool        isFine()
        {
            return this->status == 0;
        }
        
        void        run()
        {
            for (auto &pair: systemsMap)
            {
                pair.second->run();
            }
        }
        
    };
}

#endif //FEUCS_FEUCS_HPP

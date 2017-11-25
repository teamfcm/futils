//
// Created by ganz on 08/09/17.
//

#ifndef FEUCS_FEUCS_HPP
#define FEUCS_FEUCS_HPP

# include <vector>
# include <list>
# include <map>
# include <queue>
# include <typeinfo>
# include <functional>
# include <unordered_map>

namespace futils
{
// Forward declarations
    class   EntityManager;
    class   IEntity;

    class   IComponent
    {
    protected:
        IEntity     *__entity{nullptr};
        std::string __name{"[DEFAULT_COMPONENT]"};
    public:
        virtual ~IComponent() {}

        std::string const &getName() const {return this->__name;}
        void                setEntity(IEntity &ent);
        IComponent  &getAssociatedComponent(std::string const &type);
    };

    class   ISystem
    {
        std::string name{"Undefined"};
        EntityManager *entityManager{nullptr};
    public:
        virtual ~ISystem() {}
        virtual void run(float elapsed = 0) = 0;
        void provideManager(EntityManager &manager) { entityManager = &manager; }
        std::string const &getName() const { return name; }
    };

    class   IEntity
    {
        std::unordered_multimap<std::string, IComponent *>    components;
        std::function<void(IComponent &)>   registerComponentFunction{[](IComponent &){}};
        int                                 _id;

        // Replace with SFINAE or static assertion. SFINAE is probably better.
        template                            <typename Compo>
        void                                verifIsComponent()
        {
            if (!std::is_base_of<IComponent, Compo>::value)
                throw std::logic_error(std::string(typeid(Compo).name()) + " is not a Component");
        }
    public:
        IEntity()
        {
            // TODO: Change for the inline function. Its easier to read.
            this->_id = futils::UID::get();
        }
        virtual ~IEntity() {}
        virtual void    init() = 0;

        // Make the function name a bit shorter ? onExtension for example. Its only for the engine devs anyway.
        void            setComponentRegistrationFunction(std::function<void(IComponent &)> func)
        {
            this->registerComponentFunction = func;
        }

        template    <typename Compo, typename ...Args>
        Compo       &attachComponent(Args ...args)
        {
            verifIsComponent<Compo>();
            // TODO: Make a smart pointer.
            auto compo = new Compo(args...);
            compo->setEntity(*this);
            this->components.insert(std::make_pair(compo->getName(), compo));
            this->registerComponentFunction(*compo);
            return *compo;
        };

        IComponent  &getComponent(std::string const &type)
        {
            for (auto &it: this->components)
            {
                if (it.first == type)
                    return *it.second;
            }
            throw std::runtime_error("Entity does not have component " + type);
        };

        int         getId() const { return this->_id; }
    };

    class   EntityManager
    {
        int                                     status{0};
        std::multimap<std::string, ISystem *>   systemsMap;
        std::queue<std::string> systemsMarkedForErase;
    public:
        EntityManager() = default;
        template    <typename T, typename ...Args>
        T           *createEntity(Args ...args)
        {
            if (!std::is_base_of<IEntity, T>::value)
                throw std::logic_error(std::string(typeid(T).name()) + " is not an Entity");
            auto entity = new T(args...);
            entity->init();
            return entity;
        }

        template    <typename System, typename ...Args>
        void        addSystem(Args ...args)
        {
            if (!std::is_base_of<ISystem, System>::value)
                throw std::logic_error(std::string(typeid(System).name()) + " is not a System");
            auto system = new System(args...);
            system->provideManager(*this);
            this->systemsMap.insert(std::pair(system->getName(), system));
        }

        void removeSystem(std::string const &systemName)
        {
            systemsMarkedForErase.push(systemName);
        }

        bool        isFine()
        {
            return this->status == 0;
        }

        int getNumberOfSystems() const
        {
            return systemsMap.size();
        }

        void        run(float)
        {
            for (auto &pair: systemsMap)
            {
                auto &system = pair.second;
                system->run();
            }
            while (!systemsMarkedForErase.empty()) {
                auto &name = systemsMarkedForErase.front();
                systemsMap.erase(name);
                systemsMarkedForErase.pop();
            }
        }
    };
}

#endif //FEUCS_FEUCS_HPP

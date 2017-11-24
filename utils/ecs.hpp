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
        EntityManager       *entityManager{nullptr};
    public:
        virtual ~ISystem() {}
        virtual void run(float elapsed) = 0;
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
        void        registerSystem(Args ...args)
        {
            if (!std::is_base_of<ISystem, System>::value)
                throw std::logic_error(std::string(typeid(System).name()) + " is not a System");
            auto system = new System(args...);
            (void)system;
            futils::NotImplemented(__PRETTY_FUNCTION__);
//            for (auto &handledComponent: system->getRequiredComponents())
//                this->systemsMap.insert(std::pair<std::string, ISystem *>(handledComponent, system));
        }

        bool        isFine()
        {
            return this->status == 0;
        }

        // Where is the elapsed float coming from ? Probably the scene manager..
        void        run(float elapsed)
        {
            for (auto &pair: systemsMap)
            {
                pair.second->run(elapsed);
            }
        }
    };
}

#endif //FEUCS_FEUCS_HPP

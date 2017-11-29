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
# include "clock.hpp"
# include "mediator.hpp"
# include "ini.hpp"

namespace futils
{
    class   EntityManager;
    class   IEntity;

    class   IComponent
    {
    protected:
        futils::type_index _typeindex;
        IEntity     *__entity{nullptr};
        std::string __name{"[DEFAULT_COMPONENT]"};
    public:
        virtual ~IComponent() {}

        // Friend of EntityManager
        void setTypeindex(futils::type_index index) {
            _typeindex = index;
        }
        // END

        std::string const &getName() const {return this->__name;}
        void                setEntity(IEntity &ent);
        IComponent  &getAssociatedComponent(std::string const &type);
        futils::type_index getTypeindex() const {
            return _typeindex;
        }
    };

    class   ISystem
    {
    protected:
        std::string name{"Undefined"};
        EntityManager *entityManager{nullptr};
        Mediator *events{nullptr};
    public:
        virtual ~ISystem() {}
        virtual void run(float elapsed = 0) = 0;
        void provideManager(EntityManager &manager) { entityManager = &manager; }
        void provideMediator(Mediator &mediator) { events = &mediator; }
        std::string const &getName() const { return name; }
    };

    class   IEntity
    {
        std::unordered_multimap<futils::type_index, IComponent *>    components;
        int                                 _id;

        // Replace with SFINAE or static assertion. SFINAE is probably better.
        template                            <typename Compo>
        void                                verifIsComponent()
        {
            if (!std::is_base_of<IComponent, Compo>::value)
                throw std::logic_error(std::string(typeid(Compo).name()) + " is not a Component");
        }

    public:
        // TODO: SHOULD BE PRIVATE AND FRIEND WITH ENTITY MANAGER
        std::function<bool(IComponent &)> onExtension{[](IComponent &){return false;}};
        std::queue<IComponent *> lateinitComponents;
        // END.
        IEntity() {
            this->_id = futils::UID::get();
        }
        virtual ~IEntity() {}

        template    <typename Compo, typename ...Args>
        Compo       &attachComponent(Args ...args)
        {
            verifIsComponent<Compo>();
            auto compo = new Compo(args...);
            compo->setTypeindex(futils::type<Compo>::index);
            compo->setEntity(*this);
            this->components.insert(std::pair(compo->getTypeindex(), compo));
            if (onExtension(*compo) == false) {
                lateinitComponents.push(compo);
            }
            return *compo;
        };

        template <typename T>
        T &get()
        {
            for (auto &it: components)
            {
                if (it.first == futils::type<T>::index)
                    return static_cast<T &>(*it.second);
            }
            throw std::runtime_error("Entity does not have requested component");
        };

        int         getId() const { return this->_id; }
    };

    class   EntityManager
    {
        int                                     status{0};
        std::multimap<std::string, ISystem *>   systemsMap;
        std::queue<std::string> systemsMarkedForErase;
        //      Container        CompoName    Entity
        std::unordered_multimap<futils::type_index, IComponent *> components;
        std::list<std::unique_ptr<IEntity>> entities;
        futils::Clock<float> timeKeeper;
        futils::Mediator *events{nullptr};
    public:
        EntityManager() {
            timeKeeper.start();
        }

        template    <typename T, typename ...Args>
        T           &createEntity(Args ...args)
        {
            if (!std::is_base_of<IEntity, T>::value)
                throw std::logic_error(std::string(typeid(T).name()) + " is not an Entity");
            auto entity = new T(args...);
            entities.push_front(std::unique_ptr<IEntity>(entity));
            entity->onExtension = [this](IComponent &compo) {
                components.insert(std::pair(compo.getTypeindex(), &compo));
                return true;
            };
            while (!entity->lateinitComponents.empty()) {
                entity->onExtension(*entity->lateinitComponents.front());
                entity->lateinitComponents.pop();
            }
            return *entity;
        }

        template    <typename System, typename ...Args>
        void        addSystem(Args ...args)
        {
            if (!std::is_base_of<ISystem, System>::value)
                throw std::logic_error(std::string(typeid(System).name()) + " is not a System");
            // Smart Pointer
            auto system = new System(args...);
            system->provideManager(*this);
            system->provideMediator(*events);
            this->systemsMap.insert(std::pair(system->getName(), system));
        }

        void removeSystem(std::string const &systemName)
        {
            systemsMarkedForErase.push(systemName);
        }

        template <typename T>
        std::vector<T *> get()
        {
            static_assert(std::is_base_of<IComponent, T>::value, "Error : T is not a Component");
            std::vector<T *> res;
            try {
                auto range = components.equal_range(futils::type<T>::index);
                for (auto it = range.first;
                     it != range.second;
                     it++) {
                    res.push_back(static_cast<T *>(it->second));
                }
            } catch (std::exception const &e) {
                LERR(e.what());
            }
            return res;
        };

        void provideMediator(Mediator &mediator) {
            events = &mediator;
        }

        bool        isFine()
        {
            return this->status == 0;
        }

        int getNumberOfSystems() const
        {
            return systemsMap.size();
        }

        void        run()
        {
            auto elapsed = timeKeeper.loop();
            for (auto &pair: systemsMap)
            {
                auto &system = pair.second;
                system->run(elapsed);
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

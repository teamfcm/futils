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
# include "queue.hpp"

namespace futils
{
    class   EntityManager;
    class   IEntity;

    class   IComponent
    {
    protected:
        futils::type_index _typeindex;
        IEntity     *__entity{nullptr};
    public:
        virtual ~IComponent() {}

        // Friend of EntityManager
        void setTypeindex(futils::type_index index) {
            _typeindex = index;
        }
        // END

        void                setEntity(IEntity &ent) {
            __entity = &ent;
        }

        IEntity &getEntity() const
        {
            return *__entity;
        }

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
        std::function<void(EntityManager *)> afterDeath{[](EntityManager *){}};

        // It will segfault if events is not set. Be careful !
        template <typename T>
        void addReaction(std::function<void(IMediatorPacket &pkg)> fun)
        {
            events->require<T>(this, fun);
        }
    public:
        virtual ~ISystem() {}
        virtual void run(float elapsed = 0) = 0;
        void provideManager(EntityManager &manager) { entityManager = &manager; }
        void provideMediator(Mediator &mediator) { events = &mediator; }
        std::string const &getName() const { return name; }
        std::function<void(EntityManager *)> getAfterDeath()
        {
            return afterDeath;
        }
    };

    class StateSystem : public ISystem
    {
    protected:
        int phase{0};
    public:
        virtual void run(float elapsed = 0) = 0;
    };

    template <typename T>
    class ComponentAttached
    {
        void verifType() {
            static_assert(std::is_base_of<IComponent, T>::value,
                          "Cannot emit event ComponentAttached with non Component Type");
        }
    public:
        T const &compo;
        ComponentAttached(T &&compo): compo(std::forward<T>(compo)) { verifType(); }
        ComponentAttached(T const &compo): compo(compo) { verifType(); }
    };

    template <typename T>
    class ComponentDeleted
    {
        void verifType() {
            static_assert(std::is_base_of<IComponent, T>::value,
                          "Cannot emit event ComponentAttached with non Component Type");
        }
    public:
        T const &compo;
        ComponentDeleted(T &&compo): compo(std::forward<T>(compo)) { verifType(); }
        ComponentDeleted(T const &compo): compo(compo) { verifType(); }
    };

    class   IEntity
    {
        std::unordered_map<futils::type_index, IComponent *>    components;
        int                                 _id;

        template                            <typename Compo>
        void                                verifIsComponent()
        {
            if (!std::is_base_of<IComponent, Compo>::value)
                throw std::logic_error(std::string(typeid(Compo).name()) + " is not a Component");
        }
    public:
        // TODO: SHOULD BE PRIVATE AND FRIEND WITH ENTITY MANAGER
        std::function<bool(IComponent &)> onExtension{[](IComponent &){return false;}};
        std::function<void(IComponent &)> onDetach{[](IComponent &){return false;}};
        std::queue<std::pair<IComponent *, std::function<void()>>> lateinitComponents;
        futils::Mediator *events{nullptr};
        // END.
        IEntity() {
            this->_id = futils::UID::get();
        }
        virtual ~IEntity() {}

        template    <typename Compo, typename ...Args>
        Compo       &attach(Args ...args)
        {
            verifIsComponent<Compo>();
            if (components.find(futils::type<Compo>::index) != components.end())
                throw std::runtime_error(std::string("Cannot have same component twice (") + typeid(Compo).name() + ")!");
            auto compo = new Compo(args...);
            compo->setTypeindex(futils::type<Compo>::index);
            compo->setEntity(*this);
            this->components.insert(std::pair<futils::type_index, IComponent *>(compo->getTypeindex(), compo));
            if (onExtension(*compo) == false) {
                lateinitComponents.push(std::pair<Compo *, std::function<void()>>(compo, [this, compo](){
                    events->send<ComponentAttached<Compo>>(*compo);
                }));
            } else
                events->send<ComponentAttached<Compo>>(*compo);
            return *compo;
        };

        template <typename T>
        T &get() const
        {
            for (auto &it: components)
            {
                if (it.first == futils::type<T>::index)
                    return static_cast<T &>(*it.second);
            }
            throw std::runtime_error("Entity does not have requested component");
        };

        template <typename Compo>
        bool detach()
        {
            if (components.find(futils::type<Compo>::index) == components.end())
                return false;
            auto &compo = components.at(futils::type<Compo>::index);
            events->send<ComponentDeleted<Compo>>(static_cast<const Compo &>(*compo));
            components.erase(futils::type<Compo>::index);
            onDetach(*compo);
            return true;
        }

        int         getId() const { return this->_id; }
    };

    template <typename T>
    class EntityCreated
    {
        void verifType() {
            static_assert(std::is_base_of<IEntity, T>::value,
                          "Cannot emit event EntityCreated with non Entity Type");
        }
    public:
        T const &entity;
        EntityCreated(T &&entity): entity(std::forward<T>(entity)) { verifType(); }
        EntityCreated(T const &entity): entity(entity) { verifType(); }
    };

    class   EntityManager
    {
        int                                     status{0};
        std::unordered_map<std::string, ISystem *>   systemsMap;
        futils::Queue<std::string> systemsMarkedForErase;
        std::unordered_multimap<futils::type_index, IComponent *> components;
        std::list<IEntity *> entities;
        futils::Clock<float> timeKeeper;
        futils::Mediator *events{nullptr};
    public:
        EntityManager() {
            timeKeeper.start();
        }

        template    <typename T, typename ...Args>
        T           &create(Args ...args)
        {
            if (!std::is_base_of<IEntity, T>::value)
                throw std::logic_error(std::string(typeid(T).name()) + " is not an Entity");
            auto entity = new T(args...);
            entity->events = events;
            entities.push_front(entity);
            entity->onExtension = [this](IComponent &compo) {
                components.insert(std::pair<futils::type_index, IComponent *>
					(compo.getTypeindex(), &compo));
                return true;
            };
            entity->onDetach = [this](IComponent &compo) {
                // How to remove a specific component in the multimap ? :/
                auto range = components.equal_range(futils::type<T>::index);
                for (auto it = range.first;
                     it != range.second;
                     it++) {
                    auto &pair = *it;
                    auto tmp = pair.second;
                    if (tmp == &compo)
                        it = components.erase(it);
                }
            };
            events->send<EntityCreated<T>>(*entity);
            while (!entity->lateinitComponents.empty()) {
                auto front = entity->lateinitComponents.front();
                entity->onExtension(*front.first);
                front.second(); // Notification
                entity->lateinitComponents.pop();
            }
            return *entity;
        }

        template    <typename System, typename ...Args>
        void        addSystem(Args ...args)
        {
            if (!std::is_base_of<ISystem, System>::value)
                throw std::logic_error(std::string(typeid(System).name()) + " is not a System");
            // TODO : Smart Pointer !!
            auto system = new System(args...);
            system->provideManager(*this);
            system->provideMediator(*events);
            events->send<std::string>("[" + system->getName() + "] loaded.");
            this->systemsMap.insert(std::pair<std::string, ISystem *>(system->getName(), system));
        }

        void removeSystem(std::string const &systemName)
        {
            if (systemsMarkedForErase.find(systemName))
                return ;
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

        int run()
        {
            try {
                auto elapsed = timeKeeper.loop();
                for (auto &pair: systemsMap) {
                    auto &system = pair.second;
                    system->run(elapsed);
                }
                while (!systemsMarkedForErase.empty()) {
                    auto name = systemsMarkedForErase.front();
                    auto system = systemsMap.at(name);
                    events->erase(system);
                    systemsMap.erase(name);
                    auto afterDeath = system->getAfterDeath();
                    delete system;
                    events->send<std::string>("[" + name + "] shutdown.");
                    systemsMarkedForErase.pop();
                    afterDeath(this);
                }
            } catch (std::out_of_range const &)
            {
                std::cout << "Failed to erase " << systemsMarkedForErase.front() << std::endl;
                systemsMarkedForErase.pop();
            }
            return 0;
        }
    };
}

#endif //FEUCS_FEUCS_HPP

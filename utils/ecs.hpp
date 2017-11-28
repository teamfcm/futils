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
# include "ini.hpp"

namespace futils
{
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
    protected:
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
        int                                 _id;

        // Replace with SFINAE or static assertion. SFINAE is probably better.
        template                            <typename Compo>
        void                                verifIsComponent()
        {
            if (!std::is_base_of<IComponent, Compo>::value)
                throw std::logic_error(std::string(typeid(Compo).name()) + " is not a Component");
        }

    public:
        std::function<void(IComponent &)> onExtension{[](IComponent &){}};

        IEntity() {
            this->_id = futils::UID::get();
        }
        virtual void init() = 0;
        virtual ~IEntity() {}

        template    <typename Compo, typename ...Args>
        Compo       &attachComponent(Args ...args)
        {
            verifIsComponent<Compo>();
            auto compo = new Compo(args...);
            compo->setEntity(*this);
            this->components.insert(std::make_pair(futils::demangle<Compo>(), compo));
            onExtension(*compo);
            return *compo;
        };

        template <typename T>
        T &get()
        {
            for (auto &it: components)
            {
                if (it.first == futils::demangle<T>())
                    return static_cast<T &>(*it.second);
            }
            throw std::runtime_error("Entity does not have component " + futils::demangle<T>());
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
        //      Container        CompoName    Entity
        std::unordered_multimap<std::string, IComponent *> components;
        std::list<std::unique_ptr<IEntity>> entities;
        futils::Clock<float> timeKeeper;
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
                components.insert(std::pair(compo.getName(), &compo));
            };
            entity->init();
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
                auto range = components.equal_range(futils::demangle<T>());
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

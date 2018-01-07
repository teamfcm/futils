#ifndef FENDER_LIBRARY_H
#define FENDER_LIBRARY_H

# include <iostream>
# include <string>
# include <memory>
# include <functional>
# include <stack>
# include <map>
# include "futils.hpp"
# include "types.hpp"
# include "dloader.hpp"
# include "ecs.hpp"
# include "mediator.hpp"
# include "events.hpp"
# include "rendering.hpp"

# define QUOTE(str) #str
# define EXPAND_AND_QUOTE(str) QUOTE(str)

// Utils forward declarations
namespace futils
{
    class Dloader;
    class Ini;
}

namespace fender
{
    using vec2f = futils::Vec2<float>;
    using vec3f = futils::Vec3<float>;
    using vec2i = futils::Vec2<int>;
    using vec3i = futils::Vec3<int>;
    using vec2ui = futils::Vec2<unsigned int>;
    using vec3ui = futils::Vec3<unsigned int>;

    class Fender
    {
        futils::UP<futils::EntityManager> entityManager;
        futils::UP<futils::Mediator> events;
    public:
        Fender(std::string const &);
        int start();
        int run();

        void loadSystemDir(std::string const &path);

        template <typename System, typename ...Args>
        void addSystem(Args ...args) {
            entityManager->addSystem<System>(args...);
        };

		template <typename System>
		void addSystem()
		{
			entityManager->addSystem<System>();
		}
		
        template <typename System>
        void removeSystem() {
            entityManager->removeSystem(futils::demangle<System>());
        }

        template <typename T, typename ...Args>
        T *createEntity(Args ...args) {
            return entityManager->create<T>(args...);
        };
    };
}

#endif
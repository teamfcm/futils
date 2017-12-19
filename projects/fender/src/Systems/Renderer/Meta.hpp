//
// Created by arroganz on 12/19/17.
//

#ifndef FENDER_META_SYSTEM_HPP
#define FENDER_META_SYSTEM_HPP

# include <SFML/Graphics.hpp>
# include "ecs.hpp"
# include "../../Components/Meta.hpp"

namespace fender::systems {
    class Meta : public futils::ISystem {
        struct window
        {
            sf::RenderWindow *_win;
            fender::components::Meta const *_meta;
        };

        using WindowMap = std::unordered_map<std::string, window>;
        WindowMap windows;
        enum Phase
        {
            INIT = 0,
            RUN = 1
        };
        Phase phase{INIT};
        void init();
        void createNewWindow(fender::components::Meta const &);

        void refreshMetas(float elapsed);
    public:
        Meta() = default;
        void run(float) override;
    };
}
#endif //FENDER_META_SYSTEM_HPP

//
// Created by arroganz on 11/26/17.
//

#ifndef FENDER_EXTRAS_HPP
#define FENDER_EXTRAS_HPP

# include "fender.hpp"

namespace fender
{
    class Window : public futils::IEntity
    {
    public:
        Window(std::string const &name, int width, int height) {
            attachComponent<components::Windowed>(name, width, height);
        }
    };
}

#endif //FENDER_EXTRAS_HPP

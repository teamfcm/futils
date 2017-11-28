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
        Window() = default;
        void init() override {
            attachComponent<components::Windowed>("WindowName", 200, 200);
        }
    };
}

#endif //FENDER_EXTRAS_HPP

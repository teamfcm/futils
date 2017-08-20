//
// Created by ganz on 17/08/17.
//

#ifndef DEMO_FACTORY_HPP
#define DEMO_FACTORY_HPP

# include <functional>
# include <unordered_map>
# include <iostream>
# include "fender.h"
# include "Demo.hpp"
# include "ForwardScenes.hpp"

namespace demo
{
    class Factory : public fender::ISceneFactory
    {
        using map = std::unordered_map<std::string, std::function<fender::upScene(void)>>;

        map     buildFunctions;
        Demo    env;
    public:
        Factory();
        virtual fender::upScene build(std::string const &name) override;
    };
}


#endif //DEMO_FACTORY_HPP

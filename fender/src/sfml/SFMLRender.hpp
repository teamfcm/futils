//
// Created by ganz on 28/07/17.
//

#ifndef FENDER_SFMLRENDER_HPP
#define FENDER_SFMLRENDER_HPP

# include <string>
# include "fender.h"

namespace fender
{
    class SFMLRender : public IRender
    {
    public:
        SFMLRender(std::string const &string);
    };
}

#endif //FENDER_SFMLRENDER_HPP

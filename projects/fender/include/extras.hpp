//
// Created by arroganz on 11/26/17.
//

#ifndef FENDER_EXTRAS_HPP
#define FENDER_EXTRAS_HPP

# include "fender.hpp"
# include "components.hpp"

namespace fender
{
    struct Background : futils::IEntity
    {
        Background(std::string const &image = "");
    };
}

#endif //FENDER_EXTRAS_HPP

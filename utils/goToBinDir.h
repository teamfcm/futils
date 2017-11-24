//
// Created by arroganz on 11/24/17.
//

#ifndef FUTILS_GOTOBINDIR_H
#define FUTILS_GOTOBINDIR_H

# include <iostream>

namespace futils
{
    inline void goToBinDir(std::string const &path)
    {
        std::cout << path << std::endl;
    }
}

#endif //FUTILS_GOTOBINDIR_H

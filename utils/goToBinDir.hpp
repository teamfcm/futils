//
// Created by arroganz on 11/24/17.
//

#ifndef FUTILS_GOTOBINDIR_H
#define FUTILS_GOTOBINDIR_H

# include <unistd.h>
# include <iostream>

namespace futils
{
    inline void goToBinDir(std::string const &path)
    {
        auto last = path.find_last_of("/\\");
        auto dest = path.substr(0, last);
        if (chdir(dest.c_str()) != 0)
            std::cerr << "Cannot go to " + dest << std::endl;
    }
}

#endif //FUTILS_GOTOBINDIR_H

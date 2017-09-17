#include <iostream>
#include "Fini.hpp"
#include <unistd.h>

int main() {
    futils::Ini     alt("alt.ini");
    futils::Ini     file("alt.ini");
    
    alt["global"]["alt"] = false;
    alt.save();
    std::cout << file["global"]["haha"] << std::endl;
    file["global"]["haha"] = 12.4398;
    file.save();
    return 0;
}
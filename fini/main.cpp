#include <iostream>
#include "Fini.hpp"

int main() {
    futils::INI     alt("alt.ini");

    alt["windowConfig"]["width"] = 500;
    alt.save();
    return 0;
}
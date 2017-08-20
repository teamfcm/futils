#include <iostream>
#include "Fini.hpp"
#include <unistd.h>

int main() {
    futils::INI     alt("alt.ini");

    std::cout << "You can easily get values from file :" << std::endl;
    usleep(500000);
    std::cout << alt["windowConfig"]["width"] << std::endl;
    usleep(500000);
    std::cout << "And modify them either temporarily" << std::endl;
    usleep(500000);
    std::cout << "alt[\"windowConfig\"][\"width\"] = 5000;" << std::endl;
    usleep(500000);
    alt["windowConfig"]["width"] = 5000;
    usleep(500000);
    std::cout << alt["windowConfig"]["width"] << std::endl;
    usleep(500000);
    std::cout << "And when you're done : save to the file" << std::endl;
    usleep(500000);
    std::cout << "alt.save()" << std::endl;
    usleep(500000);
    alt.save();
    std::cout << "You can also save to another file easily :" << std::endl;
    usleep(500000);
    alt.save("other.ini");
    std::cout << "alt.save(\"other.ini\");" << std::endl;
    usleep(500000);
    return 0;
}
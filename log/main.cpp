#include <iostream>

# include "flog.hpp"

int main() {
    for (int i = 0; i < 103; i++)
        LOG("Je suis a la ligne " + std::to_string(i));
    return 0;
}
#include <iostream>
#include "fender.hpp"
#include "dloader.hpp"
#include "Factory.hpp"

int main()
{
    futils::Fengine engine;
    engine.start(argv[0]);
    return 0;
}

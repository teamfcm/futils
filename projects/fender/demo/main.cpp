#include <iostream>
#include "fender.hpp"
#include "dloader.hpp"
#include "Factory.hpp"

int main()
{
    futils::Fengine engine;
    return engine.start(argv[0]);
}

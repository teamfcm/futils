#include <iostream>
#include "fender.hpp"
#include "dloader.hpp"
#include "Factory.hpp"

int main(int argc, char *argv[])
{
    (void)argc;

    fender::Fender engine;
    return engine.start(argv[0]);
}

#include "App.hpp"

int main(int argc, char *argv[])
{
    demo::App app(argc, argv);

    if (app.start() != 0)
        return -1;
    return app.run();
}

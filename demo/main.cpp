#include <iostream>
#include <fstream>
#include <dlfcn.h>
#include "fender.h"
#include "DynamicLibrary.hpp"
#include "flog.hpp"
#include "Factory.hpp"

int main()
{
    START_LOG("logfile.txt");
    auto fenderDLL = futils::DynamicLibrary("./lib/fender/release/libfender.so");
    fender::ISceneFactory *factory = new demo::Factory{};
    auto manager = fenderDLL.execute<fender::Manager, fender::ISceneFactory &>("manager", *factory);
    if (manager)
    {
        manager->loadConfig("config/config.json");
        manager->loadTimeline("scenes/timeline.json");
        manager->start();
    }
    return 0;
}
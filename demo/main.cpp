#include <iostream>
#include <fstream>
#include "fender.h"
#include "DynamicLibrary.hpp"
#include "flog.hpp"
#include "Factory.hpp"

int main()
{
    START_LOG("logfile.txt");
    auto manager = futils::DynamicLibrary("./lib/fender/release/libfender.so")
            .execute<fender::Manager, fender::ISceneFactory &>
                    ("manager", *(new demo::Factory));
    if (manager)
    {
        manager->loadConfig("config/config.json");
        manager->loadTimeline("scenes/timeline.json");
        manager->start();
    }
    return 0;
}
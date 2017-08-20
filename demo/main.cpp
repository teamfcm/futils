#include <iostream>
#include <fstream>
#include "fender.h"
#include "DynamicLibrary.hpp"
#include "flog.hpp"
#include "Factory.hpp"
#include "Fini.hpp"

int main()
{
    futils::INI config("config/config.ini");

    START_LOG(config["global"]["logfile"]);
    auto manager = futils::DynamicLibrary(config["global"]["fenderPath"])
            .execute<fender::Manager, fender::ISceneFactory &>
                    ("manager", *(new demo::Factory));
    if (manager)
    {
        manager->loadConfig("config/manager.ini");
        manager->loadTimeline("scenes/timeline.ini");
        manager->start();
    }
    return 0;
}
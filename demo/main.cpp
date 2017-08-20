#include <iostream>
#include <fstream>
#include "fender.h"
#include "DynamicLibrary.hpp"
#include "flog.hpp"
#include "Factory.hpp"
#include "Fini.hpp"
#include <typeinfo>

int main()
{
    futils::INI config("config/config.ini");
    auto global{config["global"]};

    START_LOG(global["logfile"]);
    auto manager = futils::DynamicLibrary(global["fenderPath"])
            .execute<fender::Manager, fender::ISceneFactory &>
                    ("manager", *(new demo::Factory));
    if (manager)
    {
        manager->loadConfig(global["fenderConfigPath"]);
        manager->loadTimeline(global["timelineConfigPath"]);
        manager->start();
    }
    return 0;
}
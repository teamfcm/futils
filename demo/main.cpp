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

    auto dllpath = config["global"]["fenderPath"];
    START_LOG(global["logfile"]);
    auto manager = futils::DynamicLibrary(dllpath)
                           .execute<fender::Manager,
                                   fender::ISceneFactory &,
                                   futils::INI::INIProxy *>
                                   ("manager", *(new demo::Factory),
                                    config.proxy());
    if (manager)
    {
        manager->start();
    }

    return 0;
}
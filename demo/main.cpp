#include <iostream>
#include <fstream>
#include "fender.hpp"
#include "DynamicLibrary.hpp"
#include "flog.hpp"
#include "Factory.hpp"

int main()
{
    futils::INI config("config/config.ini");
    auto global{config["global"]};

    START_LOG(global["logfile"]);
    auto manager = futils::DynamicLibrary(global["fenderPath"])
                           .execute<fender::Manager,
                                   fender::ISceneFactory &,
                                   futils::INI::INIProxy *>
                                   ("manager", *(new demo::Factory),
                                    config.proxy());
    if (manager)
        manager->start();
    return 0;
}
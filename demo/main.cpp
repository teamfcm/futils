#include <iostream>
#include "fender.hpp"
#include "DynamicLibrary.hpp"
#include "log.hpp"
#include "Factory.hpp"

int main()
{
//    TODO: Remember to add goToBinDir();
    futils::Ini config("config/config.ini");
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
#include <iostream>
#include "fender.hpp"
#include "dynamicLibrary.hpp"
#include "Factory.hpp"

int main()
{
//    TODO: Remember to add goToBinDir();
    futils::Ini config("config/config.ini");

    // TODO: C'est nul c'est moche faut tout recommencer.
    START_LOG(config["global"]["logfile"]);
    auto manager = futils::DynamicLibrary(config["global"]["fenderPath"])
                           .execute<fender::Manager,
                                   fender::ISceneFactory &,
                                   futils::INI::INIProxy *>
                                   ("manager", *(new demo::Factory),
                                    config.proxy());
    if (manager)
        manager->start();
    return 0;
}
#include <iostream>
#include <dlfcn.h>
#include "fender.h"
#include "DynamicLibrary.hpp"


int main() {
    auto fenderDLL = futils::DynamicLibrary("./lib/fender/release/libfender.so");
    auto renderer = fenderDLL.execute<fender::IRender, std::string>("create", "config.json");
    if (renderer)
        renderer->hello();
    return 0;
}
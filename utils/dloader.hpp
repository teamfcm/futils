//
// Created by ganz on 28/07/17.
//

#ifndef DEMO_DLLOADER_HPP
#define DEMO_DLLOADER_HPP

#include <string>
#include <typeinfo>
#include <dlfcn.h>
#include <exception>

namespace futils
{
    class       Dloader
    {
        void            *_handle;
        std::string     _path;
    public:
        Dloader(std::string const &path, int mode = RTLD_LAZY):
                _path(path)
        {
            _handle = dlopen(path.c_str(), mode);
            if (_handle == nullptr)
                throw std::domain_error("Cannot find " + path);
        }

        template    <typename T, typename ...Args>
        T           *build(Args ...args)
        {
            std::string symbol{typeid(T).name()};
            auto func = (T *(*)(Args ...))(dlsym(_handle, symbol.c_str()));
            if (func == nullptr)
            {
                std::cerr << __FUNCTION__ << ": failed. Cannot find builder symbol "
                                             + symbol + " in " + _path << std::endl;
                return nullptr;
            }
            return func(args...);
        };

        template    <typename Ret, typename ...Args>
        Ret           execute(std::string const &symbol, Args ...args)
        {
            auto func = (Ret (*)(Args ...))(dlsym(_handle, symbol.c_str()));
            if (func == nullptr) {
                std::cerr << __FUNCTION__ << ": failed. Cannot find symbol "
                                             + symbol + " in " + _path << std::endl;
                throw std::runtime_error("Dynamic execution of " + symbol + " failed.");
            } else {
                return func(args...);
            }
        };
    };
}

#endif //DEMO_DLLOADER_HPP

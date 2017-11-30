//
// Created by Dowwind on 27/11/2017.
//

#ifndef RUTILS_RUTILSEXCEPTION_HPP
#define RUTILS_RUTILSEXCEPTION_HPP

#include <string>
#include <utility>
#include <stdexcept>

namespace rutils
{
    class FileNotFound: std::runtime_error
    {
    private:
        std::string _msg;
    public:
        explicit FileNotFound(const std::string &_Message) : runtime_error(_Message), _msg(_Message) {}

        const char *what() const throw() override { return _msg.c_str(); }
    };

    class InvalidTypeFile: std::runtime_error
    {
    private:
        std::string _msg;

    public:
        explicit InvalidTypeFile(const std::string &_Message) : runtime_error(_Message), _msg(_Message) {}

        const char *what() const throw() override { return _msg.c_str(); }

    };

    class SyntaxError: std::runtime_error
    {
    private:
        std::string _msg;

    public:
        explicit SyntaxError(const std::string &_Message) : runtime_error(_Message), _msg(_Message) {}

        const char *what() const throw() override { return _msg.c_str(); }
    };

}

#endif //RUTILS_RUTILSEXCEPTION_HPP

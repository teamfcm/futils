//
// Created by ganz on 16/08/17.
//

#ifndef LOG_FLOG_HPP
#define LOG_FLOG_HPP

# include <iostream>
# include <fstream>
# include <chrono>
# include <iomanip>
# include "futils.hpp"

#ifdef unix
# define FUNC __PRETTY_FUNCTION__
#elif _WIN32
# define FUNC __func__
#endif
# define DEFAULT_FUNC_NAME   "(undefined)"
# define START_MSG           "Start log in "
# define GET                 flog::Log::get
# define START_LOG(v)        GET(v).logAndOut(START_MSG + std::string(v), FUNC)
# define FOUT(v)              GET().out(v, FUNC)
# define FERR(v)              GET().err(v, FUNC)
# define LOG(v)              GET().logToFile(v, FUNC)
# define LOUT(v)             GET().logAndOut(v, FUNC)
# define LERR(v)             GET().logAndErr(v, FUNC)

namespace flog
{
    class   Log
    {
    private:
        std::string     previousFunc{""};
        std::string     filename;
        std::ofstream   file;
        std::mutex      mutex;
        int             line{0};

        Log(std::string const &filename):
                filename(filename), file(filename)
        {

        }

    public:
        static Log  &get(std::string filename = "")
        {
            static Log  *inst = new Log(filename);
            return *inst;
        }

        template    <typename T>
        void        logToFile(T const &obj, std::string const &func = DEFAULT_FUNC_NAME)
        {
            std::scoped_lock<std::mutex>    lock(this->mutex);

            if (this->previousFunc != func)
            {
                this->previousFunc = func;
                this->file << std::setw(6) << "[" << this->line << "] In " << func
                           << std::endl << obj << std::endl;
            }
            else
            {
                this->file << std::setw(6) << "[" << this->line << "]\t" << obj << std::endl;
            }
            this->line++;
        }

        template    <typename T>
        void        out(T const &obj, std::string const &func = DEFAULT_FUNC_NAME)
        {
            std::scoped_lock<std::mutex>    lock(this->mutex);
            if (this->previousFunc != func)
            {
                this->previousFunc = func;
                std::cout << "--> In " + func << std::endl
                          << obj << std::endl;
            }
            else
            {
                std::cout << "-->\t" << obj << std::endl;
            }

        }

        template    <typename T>
        void        err(T const &obj, std::string const &func = DEFAULT_FUNC_NAME)
        {
            std::scoped_lock<std::mutex>    lock(this->mutex);

            if (this->previousFunc != func)
            {
                this->previousFunc = func;
                std::cerr << "==> In " + func << std::endl
                          << obj << std::endl;
            }
            else
            {
                std::cerr << "==>\t" << obj << std::endl;
            }
        }

        template    <typename T>
        void        logAndOut(T const &obj, std::string const &func = DEFAULT_FUNC_NAME)
        {
            logToFile(obj, func);
            out(obj, func);
        }

        template    <typename T>
        void        logAndErr(T const &obj, std::string const &func = DEFAULT_FUNC_NAME)
        {
            logToFile(obj, func);
            err(obj, func);
        }
    };
}

#endif //LOG_FLOG_HPP

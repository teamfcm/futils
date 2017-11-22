//
// Created by arroganz on 11/21/17.
//

#ifndef TESTS_SIGCATCH_H
#define TESTS_SIGCATCH_H

# include <signal.h>
# include <functional>

namespace futils
{
    // Singleton Pattern for single interaction with the Signal API
    class SigHandler
    {
        using map = std::unordered_map<int, std::string>;
        SigHandler() {
            sigNames[1] = "SIGHUP";
            sigNames[2] =  "SIGINT";
            sigNames[3] =  "SIGQUIT";
            sigNames[4] =  "SIGILL";
            sigNames[5] =  "SIGTRAP";
            sigNames[6] =  "SIGABRT";
            sigNames[7] =  "SIGBUS";
            sigNames[8] =  "SIGFPE";
            sigNames[9] =  "SIGKILL";
            sigNames[10] =  "SIGUSR1";
            sigNames[11] =  "SIGSEGV";
            sigNames[12] =  "SIGUSR2";
            sigNames[13] =  "SIGPIPE";
        }
        map setHandlers;
        map sigNames;
    public:
        static SigHandler &inst() {
            static SigHandler *inst = new SigHandler();
            return *inst;
        }

        void set(int sig, void (*func)(int),
                 std::string const &name = "undefined")
        {
            if (setHandlers.find(sig) != setHandlers.end())
                return ;
            struct sigaction sigIntHandler;
            sigIntHandler.sa_handler = func;
            sigemptyset(&sigIntHandler.sa_mask);
            sigIntHandler.sa_flags = 0;
            sigaction(sig, &sigIntHandler, NULL);
            setHandlers[sig] = name;
        }

        std::string get(int sig) {
            std::string signame;
            if (sigNames.find(sig) == sigNames.end())
                signame = "Unknown signal " + std::to_string(sig);
            else
                signame = sigNames[sig];
            if (setHandlers.find(sig) == setHandlers.end())
                return "Signal " + signame + " not handled";
            return signame + std::string("\t is handled by ") + setHandlers[sig];
        }
    };
}

#endif //TESTS_SIGCATCH_H

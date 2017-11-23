// Test of futils::Callback

# include <iostream>
# include <criterion/criterion.h>
# include "callback.hpp"
# include "sigCatch.hpp"

std::atomic<bool> shouldContinue = true;

class test{
public:
    static void cleanExit(int sig)
    {
        std::cout << "Received signal " << sig << std::endl;
        shouldContinue = false;
    }
};

int main(void)
{
    auto handler = futils::SigHandler::inst();
    handler.set(SIGINT, test::cleanExit, "cleanExit");
    handler.set(15, test::cleanExit, "cleanExit");
    std::atomic<int> i = 0;
    futils::Callback<int> cb([&i](int a) {
        i++;
    }, 0, -1, 0.001);
    cb(1);
    while (shouldContinue)
    {
        printf("main %d\n", (int)i);
        futils::Clock<float>::sleep(0.1);
    }
    cb.stop();
    std::cout << "Stopping service." << std::endl;
}

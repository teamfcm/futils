// Test of futils::Callback

# include <iostream>
# include <criterion/criterion.h>
# include "callback.hpp"
# include "sigCatch.hpp"

std::atomic<bool> shouldContinue = true;

class test{
public:
    static void cleanExit(int)
    {
        shouldContinue = false;
    }
};

int main(void)
{
    auto handler = futils::SigHandler::inst();
    handler.set(SIGINT, test::cleanExit, "cleanExit");
    std::atomic<int> i = 0;
    futils::Callback<float> cb([&i]() {
        i++;
    }, 0, -1, 0.001);
    while (shouldContinue)
    {
        printf("main %d\n", (int)i);
        futils::Clock<float>::sleep(0.1);
    }
    cb.stop();
    std::cout << std::endl << "\t Sigint received - Stopping service." << std::endl;
}

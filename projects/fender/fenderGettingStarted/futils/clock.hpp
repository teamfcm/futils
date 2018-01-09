//
// Created by arroganz on 11/21/17.
//

#ifndef FUTILS_CLOCK_H
#define FUTILS_CLOCK_H

#include <chrono>
#include <thread>
#include <mutex>

namespace futils
{
    // Use the clock for time management
    template        <typename Step = float>
    class           Clock
    {
        using clock = std::chrono::system_clock;
        clock::time_point startPoint{clock::now()};
        clock::time_point endPoint{clock::now()};
        float buffer{0.0};
        float elapsed{0.0};

    public:
        static void sleep(Step time) // In seconds
        {
            auto duration = std::chrono::duration<Step>(time);
            std::this_thread::sleep_for(duration);
        }

        Clock()
        {

        }

        float       loop()
        {
            static auto previous = clock::now();
            elapsed = std::chrono::duration<Step>(clock::now() - previous).count();
            buffer += elapsed;
            previous = clock::now();
            return elapsed;
        }
        float       elapsedTime()
        {
            return this->buffer;
        }
        void        reset()
        {
            this->buffer = 0.0;
        }
        void        start()
        {
            this->startPoint = std::chrono::system_clock::now();
        }
        void        end()
        {
            this->endPoint = std::chrono::system_clock::now();
        }
    };
}

#endif //FUTILS_CLOCK_H

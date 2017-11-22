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
        static void sleep(Step time)
        {
            auto duration = std::chrono::duration<Step>(time);
            std::this_thread::sleep_for(duration);
        }

        Clock()
        {

        }

        float       loop()
        {
            elapsed = std::chrono::duration<Step>(this->endPoint - this->startPoint).count();
            buffer += elapsed;
            return this->elapsed;
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

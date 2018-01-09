//
// Created by arroganz on 11/21/17.
//

#ifndef FUTILS_DELAYEDTHREAD_H
#define FUTILS_DELAYEDTHREAD_H

# include <thread>
# include <memory>
# include <functional>
# include <atomic>
# include "clock.hpp"
# include "types.hpp"

namespace futils
{
    template <typename ...Args>
    class Callback
    {
        Task<Args...> _task;
        Task<Args...> _timedTask;
        std::thread _thread;
        float _delayTime;
        float _intervalTime;
        int _repetitions;
        std::atomic<bool> shouldStop{false};

        void setTimedTask()
        {
            Action _delay = [this](){
                futils::Clock<float>::sleep(this->_delayTime);
            };
            Action _timer = [this]() {
                futils::Clock<float>::sleep(static_cast<float>(this->_intervalTime));
            };
            _timedTask = [this, _delay, _timer](Args ...args){
                int localRepetition = _repetitions;
                _delay();
                while (!shouldStop && (localRepetition > 0 || _repetitions == -1)) {
                    _task(args...);
                    _timer();
                    localRepetition--;
                }
                shouldStop = true;
            };
        }

        void startTask(Args ...args)
        {
            stop();
            shouldStop = false;
            _thread = std::thread(_timedTask);
        }
    public:
        Callback(Task<Args...> task, float interval = 1, int repetions = -1, float delay = -1):
                _task(task), _delayTime(delay), _intervalTime(interval), _repetitions(repetions)
        {
            setTimedTask();
            startTask();
        }
        ~Callback() { stop(); }
        Callback &operator = (Task<Args...> task)
        {
            stop();
            _task = task;
            setTimedTask();
        }

        void call(Args ...args)
        {
            startTask(args...);
        }

        void operator () (Args... args)
        {
            call(args...);
        }

        void resume()
        {

        }

        void pause()
        {

        }

        void wait() {
            while(!shouldStop);
        }

        void stop()
        {
            shouldStop = true;
            if (_thread.joinable())
                _thread.join();
        }
    };

    template <> class Callback<void>
    {
        Action _task;
        Action _timedTask;
        std::thread _thread;
        float _delayTime;
        float _intervalTime;
        int _repetitions;
        std::atomic<bool> shouldStop{false};

        void setTimedTask()
        {
            Action _delay = [this](){
                futils::Clock<float>::sleep(this->_delayTime);
            };
            Action _timer = [this]() {
                futils::Clock<float>::sleep(static_cast<float>(this->_intervalTime));
            };
            _timedTask = [this, _delay, _timer](){
                int localRepetition = _repetitions;
                _delay();
                while (!shouldStop && (localRepetition > 0 || _repetitions == -1)) {
                    _task();
                    _timer();
                    localRepetition--;
                }
                shouldStop = true;
            };
        }

        void startTask()
        {
            stop();
            shouldStop = false;
            _thread = std::thread(_timedTask);
        }
    public:
        Callback(Action task,
                 float interval = 1,
                 int repetions = -1,
                 float delay = -1):
                _task(task), _delayTime(delay), _intervalTime(interval), _repetitions(repetions)
        {
            setTimedTask();
            startTask();
        }
        ~Callback() { stop(); }
        Callback &operator = (Action task)
        {
            stop();
            _task = task;
            setTimedTask();
            return *this;
        }

        void call()
        {
            startTask();
        }

        void operator () ()
        {
            call();
        }

        void resume()
        {

        }

        void pause()
        {

        }

        void wait() {
            while(!shouldStop);
        }

        void stop()
        {
            shouldStop = true;
            if (_thread.joinable())
                _thread.join();
        }
    };
}

#endif //FUTILS_DELAYEDTHREAD_H

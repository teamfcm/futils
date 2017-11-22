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

namespace futils
{
    template <typename Step = float, typename ...Args>
    class Callback
    {
        using function = std::function<void(Args...)>;

        std::thread _thread;
        std::function<void(void)> _delay{[](){}};
        std::function<void(void)> _timer{[](){}};
        function _callback;
        function _result;
        Step _delayTime;
        Step _intervalTime;
        int _repetitions;
        std::atomic<bool> shouldStop{false};

        void setResult()
        {
            _delay = [this](){
                futils::Clock<Step>::sleep(this->_delayTime);
            };

            _timer = [this]() {
                futils::Clock<Step>::sleep(static_cast<float>(this->_intervalTime));
            };

            _result = [this](Args ...args){
                int localRepetition = _repetitions;
                _delay();
                while (!shouldStop && (localRepetition > 0 || _repetitions == -1)) {
                    _callback(args...);
                    _timer();
                    localRepetition--;
                }
            };

            _thread = std::thread(_result);
        }
    public:
        Callback(function func,
                 Step interval = 1000,
                 int repetions = -1,
                 Step delay = 0):
                _callback(func),
                _delayTime(delay),
                _intervalTime(interval),
                _repetitions(repetions)
        {
            static_assert(std::is_arithmetic<Step>::value, "You cannot step with non arithmetic type.");
            setResult();
        }

        ~Callback() { stop(); }

        Callback &operator = (function &func)
        {
            _callback = func;
            setResult();
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

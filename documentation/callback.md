# futils::Callback

```c++
template <typename Step = float, typename ...Args>
class futils::Callback
```

Class template ```futils::Callback``` is a general purpose polymorphic callback wrapper. Instances of Callback can store any ```futils::Task``` and invoke them at a given timed interval, a given number of times and after a given delay.

## Member types

```c++
futils::Task _task
```

Used to store the user-defined task.

```c++
std::thread _thread
```

Lateinit thread for async execution of _task.

## Member functions

### Constructor

By default, a callback is not going to do anything. It will however be called in an async thread every second, forever, from the moment you **explicitly** call it the first time.
#include <iostream>
#include "Fini.hpp"
#include <thread>
#include <unistd.h>

void        thread1(int nbr)
{
    futils::Ini     thread1Ini("alt.ini");
    for (int i = 0; i < 100; i++)
    {
        thread1Ini["thread"]["status"] = "Thread " + std::to_string(nbr) + " Wins !";
        thread1Ini.save();
    }
}

int main() {
    std::vector<std::thread>    list;
    
    for (int i = 0; i < 255; i++)
    {
        list.emplace_back(thread1, i);
    }
    for (auto &t : list)
    {
        t.join();
    }
    return 0;
}
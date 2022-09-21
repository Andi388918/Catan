
#include "game.h"

#include <iostream>
#include <chrono>

int main()
{
    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < 1000; ++i)
    {
        Game game { 3 };
    }

    auto end = std::chrono::system_clock::now();
    
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

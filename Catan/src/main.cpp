
#include "game.h"

#include <iostream>
#include <chrono>

int main()
{
    Game game{ 3 };

    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < 1; ++i)
    {
        Game game_copy = game;
    }

    auto end = std::chrono::system_clock::now();
    
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

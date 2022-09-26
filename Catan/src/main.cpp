
#include "game.h"

#include <iostream>
#include <chrono>

int main()
{
    Game game_a { 3 };

    auto start = std::chrono::system_clock::now();

    for (int i {}; i < 1000; ++i)
    {
        Game game = game_a;
    }

    auto end = std::chrono::system_clock::now();
    
    std::cout << "copying: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

    start = std::chrono::system_clock::now();

    for (int i {}; i < 1000; ++i)
    {
        Game game_b { 3 };
    }

    end = std::chrono::system_clock::now();

    std::cout << "from scratch: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}


#include "board.h"
#include "distributions.hpp"

#include <iostream>
#include <chrono>

int main()
{
    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < 1000; ++i)
    {
        Board board { Distributions::hex_tiles };
    }

    auto end = std::chrono::system_clock::now();
    
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

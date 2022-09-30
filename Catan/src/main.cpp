
#include "printing.h"
#include "game.h"

#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

int main()
{
    try
    {
        auto start = std::chrono::system_clock::now();

        for (int i{}; i < 1000; ++i)
        {
            Game game{ 3 };

            int j = 0;
            while (!game.is_finished())
            {
                std::vector<int> legal_actions{ game.get_legal_actions() };
                static std::default_random_engine ran;
                int random_number{ std::uniform_int_distribution<>{0, static_cast<int>(legal_actions.size() - 1)}(ran) };
                game.move(legal_actions.at(random_number));
                ++j;
            }
        }

        auto end = std::chrono::system_clock::now();

        std::cout << "from scratch: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what();
    }
    
}

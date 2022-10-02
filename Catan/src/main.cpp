
#include "printing.h"
#include "game.h"
#include "agent.h"

#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

int main()
{
    try
    {
        auto start = std::chrono::system_clock::now();

        Agent agent;

        for (int i {}; i < 1000; ++i)
        {
            Game game { 3 };

            int j = 0;

            while (!game.is_finished())
            {
                std::vector<int> legal_actions { game.get_legal_actions() };
                int move { agent.select_move(legal_actions) };
                game.move(move);
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

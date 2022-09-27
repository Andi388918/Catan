
#include "game.h"

#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

template<class C>
void print(C& c)
{
    std::cout << "[";
    std::ranges::for_each(c, [i = std::size_t {}, &c](const auto& e) mutable
        {
            std::cout << e;
            if (i < c.size() - 1)
            {
                std::cout << ", ";
            }
            ++i;
        }
    );
    std::cout << "]" << std::endl;
}

int main()
{

    auto start = std::chrono::system_clock::now();

    for (int i {}; i < 1; ++i)
    {
        Game game { 3 };

        int j = 0;
        while (!game.is_finished())
        {
            std::vector<int> legal_actions { game.get_legal_actions() };
            // print(legal_actions);
            static std::default_random_engine ran;
            int random_number { std::uniform_int_distribution<>{0, static_cast<int>(legal_actions.size() - 1)}(ran)};
            // std::cout << legal_actions.at(random_number) << std::endl;
            game.move(legal_actions.at(random_number));
            ++j;
        }
    }

    auto end = std::chrono::system_clock::now();

    std::cout << "from scratch: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

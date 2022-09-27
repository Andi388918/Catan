#pragma once

#include <iostream>
#include <algorithm>

template<class C>
void print(C& c)
{
    std::cout << "[";
    std::ranges::for_each(c, [i = std::size_t{}, &c](const auto& e) mutable
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
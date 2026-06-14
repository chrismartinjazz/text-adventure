#ifndef UI_HELPERS_H
#define UI_HELPERS_H

#include <iostream>
#include <string>
#include <string_view>

namespace ui
{
    inline std::string ask_input(std::string_view prompt)
    {
        while (true)
        {
            std::cout << prompt;
            std::string input;
            if (!std::getline(std::cin, input))
                throw std::runtime_error("Unexpected end of input");

            if (input.length() == 0)
                continue;

            return input;
        }
    }
}; // namespace ui

#endif
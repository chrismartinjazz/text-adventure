#ifndef TEXT_HELPERS_H
#define TEXT_HELPERS_H

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace text
{
    inline const std::string whitespace = " \n\r\t\f\v";

    inline std::string downcase(std::string text)
    {
        std::transform(
            text.begin(),
            text.end(),
            text.begin(),
            [](unsigned char c) { return std::tolower(c); }
        );
        return text;
    }

    inline std::string ltrim(const std::string& text)
    {
        std::size_t start = text.find_first_not_of(whitespace);
        return (start == std::string::npos) ? "" : text.substr(start);
    }

    inline std::string rtrim(const std::string& text)
    {
        std::size_t end = text.find_last_not_of(whitespace);
        return (end == std::string::npos) ? "" : text.substr(0, end + 1);
    }

    inline std::string trim(const std::string& text)
    {
        return rtrim(ltrim(text));
    }

    inline std::string clean(const std::string& input)
    {
        return { trim(downcase(input)) };
    }

    inline std::vector<std::string>
    split_by_delimiters(std::string text, std::string delimiters = " .,;")
    {
        std::vector<std::string> tokens {};
        std::stringstream ss(text);
        std::string line;
        while (std::getline(ss, line))
        {
            std::size_t previous { 0 };
            std::size_t position {};
            while ((position = line.find_first_of(delimiters, previous)) !=
                   std::string::npos)
            {
                if (position > previous)
                    tokens.push_back(
                        line.substr(previous, position - previous)
                    );
                previous = position + 1;
            }
            if (previous < line.length())
                tokens.push_back(line.substr(previous, std::string::npos));
        }
        std::erase_if(tokens, [](const std::string& s) { return s.empty(); });
        return tokens;
    }
} // namespace text

#endif

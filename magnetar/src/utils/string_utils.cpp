#include <iostream>
#include <sstream>
#include <algorithm>
#include "magnetar/utils/string_utils.h"

static size_t find_nth_newline(const std::string &str, int n)
{
    size_t pos = -1;
    for (int i = 0; i < n; ++i)
    {
        pos = str.find('\n', pos + 1);
        if (pos == std::string::npos)
            break;
    }
    return pos;
}

std::vector<std::string> magnetar::string_utils::split(const std::string &str, char character)
{
    std::stringstream ss(str);
    std::string segment;
    std::vector<std::string> segments;
    while (std::getline(ss, segment, character))
        segments.push_back(segment);
    return segments;
}

std::string magnetar::string_utils::lowercase(const std::string &str)
{
    std::string copy(str);
    std::transform(copy.begin(), copy.end(), copy.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return copy;
}

std::string magnetar::string_utils::uppercase(const std::string &str)
{
    std::string copy(str);
    std::transform(copy.begin(), copy.end(), copy.begin(),
                   [](unsigned char c)
                   { return std::toupper(c); });
    return copy;
}

std::string magnetar::string_utils::replace(const std::string &str, char from, char to)
{
    std::string copy(str);
    std::transform(copy.begin(), copy.end(), copy.begin(),
                   [from, to](unsigned char c)
                   { return (char)c == from ? to : (char)c; });
    return copy;
}

std::string magnetar::string_utils::trim(const std::string &str)
{
    const std::string whitespace = " \t\n\r\f\v";
    const auto start = str.find_first_not_of(whitespace);
    if (start == std::string::npos)
        return "";

    const auto end = str.find_last_not_of(whitespace);
    const auto range = end - start + 1;

    return str.substr(start, range);
}

std::string magnetar::string_utils::line(const std::string &str, int line)
{
    auto index = find_nth_newline(str, line);
    auto index2 = find_nth_newline(str, line + 2);
    if (index2 == std::string::npos)
        return str.substr(index);

    return trim(str.substr(index, index2 - index - 1));
}

std::string magnetar::string_utils::remove_from_start(const std::string &string, const std::string &prefix)
{
    std::string copy = string;
    if (copy.find(prefix) == 0)
        copy.erase(0, prefix.length());
    return copy;
}
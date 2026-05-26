#include <iostream>
#include <sstream>
#include <algorithm>
#include "magnetar/utils/string_utils.h"

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

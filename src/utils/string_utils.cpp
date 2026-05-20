#include <iostream>
#include <sstream>
#include "magnetar/utils/string_utils.h"

std::vector<std::string> magnetar::string_utils::split(const std::string& str, char character)
{
    std::stringstream ss(str);
    std::string segment;
    std::vector<std::string> segments;
    while (std::getline(ss, segment, character))
        segments.push_back(segment);
    return segments;
}

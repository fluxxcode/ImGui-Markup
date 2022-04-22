#include "impch.h"
#include "utility/utility.h"

/**
 * @file utility.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of utility.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal::utils
{

bool StringToInt(const std::string& in, int& out) noexcept
{
    try
    {
        out = std::stoi(in);
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool StringToFloat(const std::string& in, float& out) noexcept
{
    try
    {
        out = std::stof(in);
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool StringToBool(const std::string& in, bool& out) noexcept
{
    if (in == "true" || in == "True" || in == "1")
        out = true;
    else if (in == "false" || in == "False" || in == "0")
        out = false;
    else
        return false;

    return true;
}

std::vector<std::string> SplitString(std::string str, const char c) noexcept
{
    std::stringstream ss(str);
    std::string segment;
    std::vector<std::string> segments;

    while (std::getline(ss, segment, c))
        segments.push_back(segment);

    return segments;
}

}  // namespace igm::internal::utils

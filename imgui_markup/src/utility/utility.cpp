#include "impch.h"
#include "utility/utility.h"

/**
 * @file utility.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of utility.h
 * @copyright Copyright (c) 2022 - 2023
 */

#include <assert.h>  // assert

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

ImGuiMouseButton ConvertMouseButton(igm::MouseButton btn) noexcept
{
    switch (btn)
    {
    case igm::MouseButton::kLeft: return ImGuiMouseButton_Left;
    case igm::MouseButton::kMiddle: return ImGuiMouseButton_Middle;
    case igm::MouseButton::kRight: return ImGuiMouseButton_Right;
    }

    assert("INTERNAL_ERROR: Undefined MouseButton");
    return ImGuiMouseButton_Left;
}

const char* ResultTypeToString(igm::ResultType type) noexcept
{
    switch (type)
    {
    case ResultType::kSuccess: return "Success";
    case ResultType::kParserError: return "ParserError";
    case ResultType::kInvalidUnitID: return "InvalidUnitID";
    case ResultType::kInvalidItemID: return "InvalidItemID";
    case ResultType::kInvalidItemType: return "InvalidItemType";
    }
    assert("Invalid result type");
    return "";
}

}  // namespace igm::internal::utils

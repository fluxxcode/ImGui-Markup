#ifndef IMGUI_MARKUP_SRC_UTILITY_UTILITY_H_
#define IMGUI_MARKUP_SRC_UTILITY_UTILITY_H_

/**
 * @file vector2_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains utility functions used internally.
 * @copyright Copyright (c) 2022
 */

#include <string>  // std::string
#include <vector>  // std::vector

namespace igm::internal::utils
{

bool StringToInt(const std::string& in, int& out) noexcept;
bool StringToFloat(const std::string& in, float& out) noexcept;
bool StringToBool(const std::string& in, bool& out) noexcept;

std::vector<std::string> SplitString(std::string str, const char c) noexcept;

}  // namespace igm::internal::utils

#endif  // IMGUI_MARKUP_SRC_UTILITY_UTILITY_H_

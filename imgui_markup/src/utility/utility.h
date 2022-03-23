#ifndef IMGUI_MARKUP_SRC_UTILITY_UTILITY_H_
#define IMGUI_MARKUP_SRC_UTILITY_UTILITY_H_

namespace igm::internal::utils
{

bool StringToInt(const std::string& in, int& out) noexcept;
bool StringToFloat(const std::string& in, float& out) noexcept;
bool StringToBool(const std::string& in, bool& out) noexcept;

}  // namespace igm::internal::utils

#endif  // IMGUI_MARKUP_SRC_UTILITY_UTILITY_H_

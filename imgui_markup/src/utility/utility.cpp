#include "impch.h"
#include "utility/utility.h"

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

}  // namespace igm::internal::utils

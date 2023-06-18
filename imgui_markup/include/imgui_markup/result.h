#ifndef IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_RESULT_H_
#define IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_RESULT_H_

/**
 * @file result.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains the main result struct used by the API.
 * @copyright Copyright (c) 2022
 */

#include <string>  // std::string

namespace igm
{

enum class ResultType : unsigned char
{
    kSuccess,
    kParserError,
    kInvalidUnitID,
    kInvalidItemID,
    kInvalidItemType
};

struct Result
{
    Result()
        : type(ResultType::kSuccess), message("Success")
    { }

    Result(ResultType type, std::string message)
        : type(type), message(message)
    { }

    ResultType type;
    std::string message;
};

}  // namespace igm

#endif  // IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_RESULT_H_

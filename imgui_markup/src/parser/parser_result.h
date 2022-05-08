#ifndef IMGUI_MARKUP_SRC_PARSER_PARSER_RESULT_H_
#define IMGUI_MARKUP_SRC_PARSER_PARSER_RESULT_H_

/**
 * @file result.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains the result of the parser; only used internally.
 * @copyright Copyright (c) 2022
 */

#include <string>
#include <vector>

namespace igm::internal
{

struct ParserPosition
{
    ParserPosition(std::vector<std::string> file_stack, std::string line,
                  size_t line_number, size_t start, size_t end);

    std::vector<std::string> file_stack;
    std::string line;
    size_t line_number;

    size_t start;
    size_t end;
};

enum class ParserResultType : unsigned char
{
    kSuccess,
    kError
};

struct ParserResult
{
    ParserResult();
    ParserResult(ParserResultType type, std::string message,
                 ParserPosition position);

    const ParserResultType type;
    const std::string message;
    const ParserPosition position;

    std::string ToString() const;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_PARSER_PARSER_RESULT_H_

#include "impch.h"
#include "parser/parser_result.h"

/**
 * @file imgui_markup.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of parser_result.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

/* ParserPosition */
ParserPosition::ParserPosition(
    std::vector<std::string> file_stack, std::string line, size_t line_number,
    size_t start, size_t end)
    : file_stack(file_stack), line(line),
      line_number(line_number), start(start), end(end)
{ }

/* ParseResult */
ParserResult::ParserResult()
    : type(ParserResultType::kSuccess), message("Success"),
      position(ParserPosition({ }, "", 0, 0, 0))
{ }

ParserResult::ParserResult(ParserResultType type, std::string message,
                           ParserPosition position)
    : type(type), message(message), position(position)
{ }

std::string ParserResult::ToString() const
{
    // TODO: Rework function, this is currently just for debugging

    std::string message;

    for (const auto& file : this->position.file_stack)
        message += file + "\n";

    message += "Error: " + this->message + "\n";
    message += "Line " + std::to_string(this->position.line_number) +":\n";

    message += this->position.line + "\n";

    std::string line_indicator;

    for (unsigned int i = this->position.line.size(); i > 0; i--)
    {
        if (i - 1 >= this->position.start && i - 1 <= this->position.end)
            line_indicator.insert(line_indicator.begin(), '^');
        else
            line_indicator.insert(line_indicator.begin(), ' ');
    }

    message += line_indicator + "\n";

    return message;
}

}  // namespace igm::internal

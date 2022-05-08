#include "impch.h"
#include "imgui_markup.h"

/**
 * @file imgui_markup.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of imgui_markup.h
 * @copyright Copyright (c) 2022
 */

#include "common/unit_stack.h"
#include "parser/parser.h"
#include "parser/parser_result.h"

namespace igm
{

size_t ParseFromFile(const char* path, bool* result_out)
{
    if (result_out)
        *result_out = false;

    internal::Unit& unit = internal::UnitStack::CreateEmptyUnit();
    internal::Parser parser(unit);

    const internal::ParserResult result = parser.ParseFromFile(path);
    if (result.type != internal::ParserResultType::kSuccess)
    {
        internal::UnitStack::SetLastResult(unit.unit_id,
            Result(ResultType::kParserError, result.ToString()));

        return unit.unit_id;
    }

    if (result_out)
        *result_out = true;

    return unit.unit_id;
}

void DeleteUnit(size_t unit, bool* result)
{
    internal::UnitStack::DeleteUnit(unit, result);
}

Result GetLastResult(size_t unit, bool* result)
{
    return internal::UnitStack::GetLastResult(unit, result);
}

}  // namespace igm

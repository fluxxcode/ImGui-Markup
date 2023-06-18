#ifndef IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_
#define IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_

/**
 * @file unit_stack.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains unit and global unit stack
 * @copyright Copyright (c) 2022 - 2023
 */

#include "common/unit.h"
#include "items/item_base.h"
#include "items/item_api.h"
#include "items/root_item.h"
#include "imgui_markup/result.h"
#include "utility/utility.h"

#include <map>  // std::map
#include <vector>  // std::vector

namespace igm::internal
{

class UnitStack
{
public:
    UnitStack(const UnitStack&) = delete;
    void operator=(UnitStack const&) = delete;

    static Unit& CreateEmptyUnit();
    static void DeleteUnit(size_t unit, bool* result = nullptr);

    static void SetLastResult(Result result);
    static Result GetLastResult();

    static Unit* GetUnit(size_t unit, bool* result);
    static ItemAPI* GetItemAPI(size_t unit, const char* item_id,
                               bool* result = nullptr);

    // Helper functions
    inline static void Error(igm::ResultType type, bool* result)
    {
        UnitStack::SetLastResult(
            Result(type, internal::utils::ResultTypeToString(type)));
        if (result)
            *result = false;
    }

    inline static void Success(bool* result)
    {
        UnitStack::SetLastResult(Result(igm::ResultType::kSuccess,
            internal::utils::ResultTypeToString(igm::ResultType::kSuccess)));
        if (result)
            *result = true;
    }

private:
    // Main buffer holding every loaded unit
    std::map<size_t, std::unique_ptr<Unit>> unit_stack_;
    Result last_result_ = Result();

    size_t unit_count_ = 0;

    UnitStack() { };
    static UnitStack& Get();

    Unit& IMPL_CreateEmptyUnit();
    void IMPL_DeleteUnit(size_t unit, bool* result);

    void IMPL_SetLastResult(Result result);
    Result IMPL_GetLastResult();

    Unit* IMPL_GetUnit(size_t unit, bool* result);
    ItemAPI* IMPL_GetItemAPI(size_t unit, const char* item_id, bool* result);
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_

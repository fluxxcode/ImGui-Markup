#ifndef IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_
#define IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_

/**
 * @file unit_stack.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains unit and global unit stack
 * @copyright Copyright (c) 2022
 */

#include "common/units/unit_base.h"
#include "common/units/gui_unit.h"
#include "common/units/theme_unit.h"
#include "items/item_base.h"
#include "items/item_api.h"
#include "items/root_item.h"
#include "imgui_markup/result.h"

#include <map>  // std::map
#include <vector>  // std::vector

namespace igm::internal
{

class UnitStack
{
public:
    UnitStack(const UnitStack&) = delete;
    void operator=(UnitStack const&) = delete;

    static UnitBase& CreateEmptyUnit(UnitType type);
    static void DeleteUnit(size_t unit, bool* result = nullptr);

    static void SetLastResult(size_t unit, Result result);
    static Result GetLastResult(size_t unit, bool* result = nullptr);

    static UnitBase* GetUnit(size_t unit, bool* result);
    static ItemAPI* GetItemAPI(size_t unit, const char* item_id,
                               bool* result = nullptr);

private:
    // Main buffer holding every loaded unit
    std::map<size_t, std::unique_ptr<UnitBase>> unit_stack_;
    std::map<size_t, Result> last_results_;

    size_t unit_count_ = 0;

    UnitStack() { };
    static UnitStack& Get();

    UnitBase& IMPL_CreateEmptyUnit(UnitType type);
    void IMPL_DeleteUnit(size_t unit, bool* result);

    void IMPL_SetLastResult(size_t unit, Result result);
    Result IMPL_GetLastResult(size_t unit, bool* result);

    UnitBase* IMPL_GetUnit(size_t unit, bool* result);
    ItemAPI* IMPL_GetItemAPI(size_t unit, const char* item_id, bool* result);
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_

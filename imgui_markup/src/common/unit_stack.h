#ifndef IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_
#define IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_

/**
 * @file unit_stack.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains unit and global unit stack
 * @copyright Copyright (c) 2022
 */

#include "items/item_base.h"
#include "imgui_markup/result.h"

namespace igm::internal
{

struct Unit
{
    Unit(size_t id)
        : unit_id(id)
    { }

    // Holds the main item tree within this unit
    std::vector<std::unique_ptr<ItemBase>> item_tree;

    // Contains mapping of the item ids to the item itself
    std::map<std::string, ItemBase*> item_ids;

    const size_t unit_id;
};

class UnitStack
{
public:
    UnitStack(const UnitStack&) = delete;
    void operator=(UnitStack const&) = delete;

    static Unit& CreateEmptyUnit();
    static void DeleteUnit(size_t unit, bool* result = nullptr);

    static void SetLastResult(size_t unit, Result result);
    static Result GetLastResult(size_t unit, bool* result = nullptr);

private:
    // Main buffer holding every loaded unit
    std::map<size_t, Unit> unit_stack_;
    std::map<size_t, Result> last_results_;

    size_t unit_count_ = 0;

    UnitStack() { };
    static UnitStack& Get();

    Unit& IMPL_CreateEmptyUnit();
    void IMPL_DeleteUnit(size_t unit, bool* result);

    void IMPL_SetLastResult(size_t unit, Result result);
    Result IMPL_GetLastResult(size_t unit, bool* result);
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_

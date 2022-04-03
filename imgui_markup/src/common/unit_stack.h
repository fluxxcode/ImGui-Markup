#ifndef IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_
#define IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_

#include "items/item_base.h"

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

private:
    // Main buffer holding every loaded unit
    std::map<size_t, Unit> unit_stack_;

    size_t unit_count_ = 0;

    UnitStack() { };
    static UnitStack& Get();

    Unit& IMPL_CreateEmptyUnit();
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_COMMON_UNIT_STACK_H_
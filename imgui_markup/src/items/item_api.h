#ifndef IMGUI_MARKUP_SRC_ITEM_ITEM_API_H_
#define IMGUI_MARKUP_SRC_ITEM_ITEM_API_H_

// Contains functions and deafult return value that can be
// called via the backend

namespace igm::internal
{

struct ItemAPI
{
    virtual void Update() noexcept = 0;

    virtual bool IsPressed() noexcept { return false; }
    virtual bool IsHovered() noexcept { return false; }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEM_ITEM_API_H_

#ifndef IMGUI_MARKUP_SRC_ITEM_ITEM_API_H_
#define IMGUI_MARKUP_SRC_ITEM_ITEM_API_H_

/**
 * @file item_api.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains the main item API class.
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

/**
 * Parent of every item within the markup language,
 * containing API functions and their default return values.
 */
struct ItemAPI
{
    virtual void API_Update() noexcept = 0;

    virtual bool API_IsPressed() noexcept { return false; }
    virtual bool API_IsHovered() noexcept { return false; }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEM_ITEM_API_H_

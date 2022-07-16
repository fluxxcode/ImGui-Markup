#ifndef IMGUI_MARKUP_SRC_ITEMS_WIDGETS_WIDGET_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_WIDGETS_WIDGET_BASE_H_

/**
 * @file widget_base.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains base for every widget item within the markup language.
 * @copyright Copyright (c) 2022
 */

#include "items/item_base.h"

namespace igm::internal
{

class WidgetBase : public ItemBase
{
public:
    WidgetBase(ItemType type, std::string id, ItemBase* parent);
    WidgetBase(const WidgetBase&) = delete;

    /**
     * Returns the full size of the item, including its margin.
     * The item size is calculated if the item is not initialized.
     * (Usually initialized after the first frame)
     */
    bt::Vector2 GetSize() const noexcept;

    /**
     * Returns the current position of the item.
     */
    bt::Vector2 GetPosition() const noexcept;

    /**
     * Implementation of the ItemBase::Update function.
     * Handles position and size including override,
     * pushes and pops an unique ImGui ID and calls WidgetUpdate().
     * Can be overwritten to prevent it.
     */
    virtual void Update(bt::Vector2 position, bt::Vector2 available_size,
                        bool dynamic_w, bool dynamic_h) noexcept;

private:
    /**
     * Top left position of the item.
     * This is the position set by the parent item or
     * overwritten via the markup language.
     */
    bt::Vector2 position_;

    /**
     * Current size of the item, including margin.
     */
    bt::Vector2 size_;

    /**
     * ImGui position of the item, without margin.
     * This is the position that is parsed to the inheriting item through the
     * WidgetUpdate function.
     */
    bt::Vector2 item_draw_position_;

    /**
     * ImGui size of the item, without margin.
     * This is the size that is parsed to the inheriting item through the
     * WidgetUpdate function.
     */
    bt::Vector2 item_draw_size_;

    /**
     * Overwrites the position that is set by the parent item.
     * Can be set via the markup language.
     */
    Vector2Wrapper position_overwrite_;

    /**
     * Overwrites the size that is set by the parent item.
     * Unlike the available size, this does not including margin!
     * Can be set via the markup language.
     */
    Vector2Wrapper size_overwrite_;

    /**
     * Margin of the item, set via the markup language.
     */
    MarginWrapper margin_;

    // TODO: Add attribute to enable or disable clipping

    /**
     * Is the item visible?
     */
    bool visible_ = true;

    /**
     * Color of the clipping area, only used for debugging purposes.
     */
    // ImColor clipping_area_color_ = ImColor(1.0f, 0.0f, 0.0f, 0.5);


    void BeginPosition(bt::Vector2 position) noexcept;

    void BeginSize(bt::Vector2 available_size, bool& dynamic_w, bool& dynamic_h)
                   noexcept;
    void EndSize(bool dynamic_w, bool dynamic_h) noexcept;

    void BeginClippingArea() const noexcept;
    void EndClippingArea() const noexcept;

    /**
     * Calcualtes and estimates the item size including margin.
     */
    bt::Vector2 CalcSize() const noexcept;

    /**
     * Main update function that should be implemented by the
     * inheriting item.
     * When implemented, the ImGui ID, margin, size and position overrides
     * are already handled and don't have to be managed by the
     * inheriting item.
     */
    virtual void WidgetUpdate(bt::Vector2 position,
                              bt::Vector2 size) noexcept { }

    /**
     * Is the item initialized? Especially important for the size,
     * since it is only set after the first frame and otherwise
     * has to be calculated.
     * The function is implemented by the inheriting item.
     */
    virtual bool IsInitialized() const noexcept = 0;

    /**
     * Gets the actual ImGui item size after the first frame.
     * Only called if dynamic_w or dynamic_h in the Update function is enabled.
     */
    virtual bt::Vector2 GetActualSize() const noexcept = 0;

    /**
     * Calcualtes and estimates the ImGui item size. (Not including margin!)
     * Used before the item is fully initialized and implemented by the
     * inheriting item.
     * This function is currently only called a single time since
     * the result is cached.
     */
    virtual bt::Vector2 CalcItemSize() const noexcept = 0;

    /**
     * Update function of the Item API, usually called for items
     * that are at the root of the item tree.
     * Currently only calls the Update function.
     */
    virtual void API_Update(bt::Vector2 position, bt::Vector2 size) noexcept;

    // See item_base.h for more information
    virtual bool OnProcessStart(std::string& error_message) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_WIDGETS_WIDGET_BASE_H_

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
    WidgetBase(ItemType type, std::string id, ItemBase* parent,
               bool create_clipping_area_ = true);

    WidgetBase(const WidgetBase&) = delete;

    /**
     * Implementation of the ItemBase::Update function.
     * Handles position and size including overwrite,
     * pushes and pops an unique ImGui ID and calls WidgetUpdate().
     */
    void Update(bt::Vector2 position, bt::Vector2 size) noexcept;

    /**
     * Calculates the size of the item before the first frame.
     * Otherwise returns the actual item size including margin.
     */
    bt::Vector2 GetSize() const noexcept;

    /**
     * Update function of the Item API, usually called for items
     * that are at the root of the item tree.
     * Currently only calls the Update function.
     */
    virtual void API_Update(bt::Vector2 position, bt::Vector2 size) noexcept;

protected:
    /**
     * Are position and size already initialized?
     * Usually set after the first frame.
     */
    bool initialized_ = false;

    /**
     * Main update function that should be implemented by the
     * inheriting item.
     */
    virtual void WidgetUpdate(bt::Vector2 position,
                              bt::Vector2 size) noexcept { }

private:
    bt::Vector2 position_;
    bt::Vector2 size_;

    /**
     * Cache for the calculated size, as this can be quite expensive fo
     * certain items and it is possible that the function is
     * called several times.
     */
    mutable bt::Vector2 calculated_size_cache_;
    mutable bool calculated_size_ = false;

    Vector2Wrapper position_overwrite_;
    Vector2Wrapper size_overwrite_;
    MarginWrapper margin_;

    bool is_visible_ = false;

    bt::Vector4 clipping_area_border_color_ = bt::Vector4(0.0f, 1.0f, 0.2f,
                                                          0.5f);

    /**
     * Should a clipping area be created?
     * Make sure to only use the clipping area on widgets placed
     * within a panel, otherwise an exception is thrown.
     * The value is set by the constructor.
     *
     * TODO: Ability to use the clipping area on items that are not placed
     *       within a panel. This would allow to e.g. create clipping
     *       areas for panels placed within views.
     */
    const bool create_clipping_area_ = false;

    /**
     * Adds margin and applies overwrite for position and size.
     * Called before the WidgetUpdate function.
     */
    void PreparePositionAndSize(bt::Vector2& position,
                                bt::Vector2& size) const noexcept;

    /**
     * Updates the WidgetBase position and size values.
     * Called after the WidgetUpdate function.
     */
    void UpdatePositionAndSize(const bt::Vector2& prepared_position,
                               const bt::Vector2& prepared_size) noexcept;

    // TODO: Implementation
    void BeginClippingArea() noexcept;
    void EndClippingArea() const noexcept;

    /**
     * Calcualtes the item size including margin.
     */
    bt::Vector2 CalcFullSize() const noexcept;

    /**
     * Function used to calculate the item size before the first frame.
     */
    virtual bt::Vector2 CalcItemSize() const noexcept = 0;

    /**
     * Gets the actual size of the item. Called after every WidgetUpdate.
     */
    virtual bt::Vector2 GetActualSize() const noexcept = 0;

    // See item_base.h for more information
    virtual bool OnProcessStart(std::string& error_message) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_WIDGETS_WIDGET_BASE_H_

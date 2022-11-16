#ifndef IMGUI_MARKUP_SRC_ITEMS_STYLE_THEME_H_
#define IMGUI_MARKUP_SRC_ITEMS_STYLE_THEME_H_

/**
 * @file theme.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'Theme'
 * @copyright Copyright (c) 2022
 */

#include "items/item_base.h"

namespace igm::internal
{

class Theme : public ItemBase
{
public:
    Theme(std::string id, ItemBase* parent);

    void PushStyle() const noexcept;
    void PopStyle() const noexcept;

private:
    // See item_base.h for more information
    bool OnProcessStart(std::string& error_message) noexcept;
    // See item_base.h for more information
    bool OnProcessEnd(std::string& error_message) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_STYLE_THEME_H_

#ifndef IMGUI_MARKUP_SRC_ITEMS_OTHER_CONTAINER_H_
#define IMGUI_MARKUP_SRC_ITEMS_OTHER_CONTAINER_H_

/**
 * @file container.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'Container'
 * @copyright Copyright (c) 2022
 */

#include "items/other/other_base.h"

#include "imgui.h"  // ImGuiMouseButton

#include <string>  // std::string

namespace igm::internal
{

class Container : public OtherBase
{
public:
    Container(std::string id, ItemBase* parent);

    void Update(bt::Vector2 position, bt::Vector2 available_size,
                bool dynamic_w, bool dynamic_h) noexcept;

    inline bt::Vector2 GetPosition() const noexcept { return this->position_; }
    inline bt::Vector2 GetSize() const noexcept { return this->size_; }

private:
    bt::Vector2 position_;
    bt::Vector2 size_;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_OTHER_CONTAINER_H_

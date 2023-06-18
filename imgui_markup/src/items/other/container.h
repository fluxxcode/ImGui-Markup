#ifndef IMGUI_MARKUP_SRC_ITEMS_OTHER_CONTAINER_H_
#define IMGUI_MARKUP_SRC_ITEMS_OTHER_CONTAINER_H_

/**
 * @file container.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'Container'
 * @copyright Copyright (c) 2022 - 2023
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

private:
    // See item_base.h for more information
    bool OnProcessEnd(std::string& error_message) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_OTHER_CONTAINER_H_

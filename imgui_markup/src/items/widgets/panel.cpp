#include "impch.h"
#include "items/widgets/panel.h"

namespace igm::internal
{

void Panel::Update() noexcept
{
    // TODO: Implementation

    std::cout << this->access_id_ << ": Updating panel" << std::endl;

    for (const auto& child : this->child_items_)
        child->Update();
}

}  // namespace igm::internal

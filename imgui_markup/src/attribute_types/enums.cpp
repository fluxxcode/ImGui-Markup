#include "impch.h"
#include "attribute_types/enums.h"

/**
 * @file enums.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of enums.h
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/string_wrapper.h"

namespace igm::internal
{

bool TestEnumWrapper::LoadValue(const StringWrapper& val) noexcept
{
    if (val.ToString() == "TestValue0")
        this->SetValue(TestEnum::kTestValue0);
    else if (val.ToString() == "TestValue1")
        this->SetValue(TestEnum::kTestValue1);
    else if (val.ToString() == "TestValue2")
        this->SetValue(TestEnum::kTestValue2);
    else
        return false;

    return true;
}

bool TestEnumWrapper::InitReference(TestEnumWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<TestEnum>*)&ref);
    return true;
}

}  // namespace igm::internal

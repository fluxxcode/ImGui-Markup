#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ENUMS_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ENUMS_H_

/**
 * @file enums.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains enum classes used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/attribute_base.h"

namespace igm::internal
{

enum class TestEnum : unsigned char
{
    kTestValue0,
    kTestValue1,
    kTestValue2
};

class TestEnumWrapper : public AttributeBase<TestEnum>
{
public:
    TestEnumWrapper()
        : AttributeBase(AttributeType::kEnum, TestEnum::kTestValue0)
    { }

    explicit TestEnumWrapper(TestEnum value)
        : AttributeBase(AttributeType::kEnum, value)
    { }

    operator TestEnum() const { return this->GetValue(); }

    inline std::string ToString() const noexcept
    {
        switch(this->GetValue())
        {
        case TestEnum::kTestValue0: return "TestEnum::TestValue0";
        case TestEnum::kTestValue1: return "TestEnum::TestValue1";
        case TestEnum::kTestValue2: return "TestEnum::TestValue2";
        default: return "TestEnum::UNDEFINED";
        }
    }

private:
    bool LoadValue(const StringWrapper& val) noexcept;

    bool InitReference(TestEnumWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ENUMS_H_

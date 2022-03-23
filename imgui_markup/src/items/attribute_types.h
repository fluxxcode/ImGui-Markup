#ifndef IMGUI_MARKUP_SRC_ITEMS_ATTRIBUTE_TYPES_H_
#define IMGUI_MARKUP_SRC_ITEMS_ATTRIBUTE_TYPES_H_

#include "imgui_markup/types.h"

namespace igm::internal
{

struct AttributeInterface
{
    virtual bool LoadValue(int value) noexcept { return false; };
    virtual bool LoadValue(float value) noexcept { return false; };
    virtual bool LoadValue(bool value) noexcept { return false; };
    virtual bool LoadValue(const char* value) noexcept { return false; };

    // TODO: Implement reference system
    // virtual bool InitReference(IntWrapper& ref) noexcept { return false; }
    // virtual bool InitReference(FloatWrapper& ref) noexcept { return false; }
    // virtual bool InitReference(BoolWrapper& ref) noexcept { return false; }
    // virtual bool InitReference(StringWrapper& ref) noexcept { return false; }
};

template<typename T>
class AttributeBase : public AttributeInterface
{
public:
    AttributeBase(T value)
        : value(value)
    { }

protected:
    inline const T& GetValue() const noexcept
    {
        // TODO: Implement reference system and keep track of all
        //       references pointing to this
        return this->value;
    }

    inline void SetValue(T value) noexcept
    {
        // TODO: Implement reference system and keep track of all
        //       references pointing to this
        this->value = value;
    }

private:
    T value;

};

class IntWrapper : public AttributeBase<int>
{
public:
    IntWrapper()
        : AttributeBase(0)
    { }

    IntWrapper(int value)
        : AttributeBase(value)
    { }

    inline operator int() const { return this->GetValue(); }

private:
    bool LoadValue(const char* value) noexcept;
    bool LoadValue(int value) noexcept;
};

class FloatWrapper : public AttributeBase<float>
{
public:
    FloatWrapper()
        : AttributeBase(0.0f)
    { }

    FloatWrapper(float value)
        : AttributeBase(value)
    { }

    inline operator float() const { return this->GetValue(); }

private:
    bool LoadValue(const char* value) noexcept;
    bool LoadValue(float value) noexcept;
};

class BoolWrapper : public AttributeBase<bool>
{
public:
    BoolWrapper()
        : AttributeBase(false)
    { }

    BoolWrapper(bool value)
        : AttributeBase(value)
    { }

    inline operator bool() const { return this->GetValue(); }

private:
    bool LoadValue(const char* value) noexcept;
    bool LoadValue(bool value) noexcept;
};

class StringWrapper : public AttributeBase<std::string>
{
public:
    StringWrapper()
        : AttributeBase(std::string())
    { }

    StringWrapper(std::string value)
        : AttributeBase(value)
    { }

    inline operator std::string() const { return this->GetValue(); }

private:
    bool LoadValue(const char* value) noexcept;
};


}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ATTRIBUTE_TYPES_H_

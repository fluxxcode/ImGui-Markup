#ifndef IMGUI_MARKUP_SRC_ITEMS_ATTRIBUTE_TYPES_H_
#define IMGUI_MARKUP_SRC_ITEMS_ATTRIBUTE_TYPES_H_

#include "imgui_markup/types.h"

namespace igm::internal
{

class IntWrapper;
class FloatWrapper;
class BoolWrapper;
class StringWrapper;

struct AttributeInterface
{
    virtual bool LoadValue(int value) noexcept { return false; };
    virtual bool LoadValue(float value) noexcept { return false; };
    virtual bool LoadValue(bool value) noexcept { return false; };
    virtual bool LoadValue(const char* value) noexcept { return false; };

    virtual bool InitReference(IntWrapper& ref) noexcept { return false; }
    virtual bool InitReference(FloatWrapper& ref) noexcept { return false; }
    virtual bool InitReference(BoolWrapper& ref) noexcept { return false; }
    virtual bool InitReference(StringWrapper& ref) noexcept { return false; }
};

template<typename T>
class AttributeBase : public AttributeInterface
{
public:
    AttributeBase(T value)
        : value_(value)
    { }

    virtual ~AttributeBase()
    {
        for (auto* reference : this->tracked_references_)
            reference->RemoveReference();
    }

    inline const T& GetValue() noexcept
    {
        if (this->reference_)
            this->value_ = this->reference_->GetValue();

        return this->value_;
    }

    inline void SetValue(T value) noexcept
    {
        if (this->reference_)
            this->reference_->SetValue(value);

        this->value_ = value;
    }

    inline void TrackReference(AttributeBase<T>* ref)
    {
        this->tracked_references_.push_back(ref);
    }

    inline void RemoveReference()
    {
        this->reference_ = nullptr;
    }

protected:
    inline void IMPL_InitReference(AttributeBase<T>* reference)
    {
        this->reference_ = reference;
        reference->TrackReference(this);
    }

private:
    T value_;
    AttributeBase<T>* reference_ = nullptr;

    // Every reference pointing to this.
    std::vector<AttributeBase<T>*> tracked_references_;
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

    inline operator int() { return this->GetValue(); }

private:
    bool LoadValue(const char* value) noexcept;
    bool LoadValue(int value) noexcept;

    bool InitReference(IntWrapper& ref) noexcept;
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

    inline operator float() { return this->GetValue(); }

private:
    bool LoadValue(const char* value) noexcept;
    bool LoadValue(float value) noexcept;

    bool InitReference(FloatWrapper& ref) noexcept;
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

    inline operator bool() { return this->GetValue(); }

private:
    bool LoadValue(const char* value) noexcept;
    bool LoadValue(bool value) noexcept;

    bool InitReference(BoolWrapper& ref) noexcept;
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

    inline operator std::string() { return this->GetValue(); }

private:
    bool LoadValue(const char* value) noexcept;

    bool InitReference(StringWrapper& ref) noexcept;
};


}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ATTRIBUTE_TYPES_H_

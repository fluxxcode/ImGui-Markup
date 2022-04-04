#ifndef IMGUI_MARKUP_SRC_ITEMS_ATTRIBUTE_TYPES_H_
#define IMGUI_MARKUP_SRC_ITEMS_ATTRIBUTE_TYPES_H_

#include "imgui_markup/types.h"

namespace igm::internal
{

enum class AttributeType
{
    kInt,
    kFloat,
    kBool,
    kString,
    kVector2,
    kVector4
};

std::string AttributeTypeToString(AttributeType type);

// Forward declaration for references
class IntWrapper;
class FloatWrapper;
class BoolWrapper;
class StringWrapper;
class Vector2Wrapper;
class Vector4Wrapper;

struct AttributeInterface
{
    inline virtual AttributeType GetType() const noexcept = 0;

    inline virtual std::string ToString() noexcept = 0;

    virtual bool LoadValue(int value) noexcept { return false; };
    virtual bool LoadValue(float value) noexcept { return false; };
    virtual bool LoadValue(bool value) noexcept { return false; };
    virtual bool LoadValue(const char* value) noexcept { return false; };
    virtual bool LoadValue(Vector2 value) noexcept { return false; };
    virtual bool LoadValue(Vector4 value) noexcept { return false; };

    virtual bool InitReference(IntWrapper& ref) noexcept { return false; }
    virtual bool InitReference(FloatWrapper& ref) noexcept { return false; }
    virtual bool InitReference(BoolWrapper& ref) noexcept { return false; }
    virtual bool InitReference(StringWrapper& ref) noexcept { return false; }
    virtual bool InitReference(Vector2Wrapper& ref) noexcept { return false; }
    virtual bool InitReference(Vector4Wrapper& ref) noexcept { return false; }
};

template<typename T>
class AttributeBase : public AttributeInterface
{
public:
    AttributeBase(AttributeType type, T value)
        : value_(value), type_(type)
    { }

    virtual ~AttributeBase()
    {
        for (auto* reference : this->tracked_references_)
        {
            if (reference)
                reference->RemoveReference();
        }
    }

    inline virtual AttributeType GetType() const noexcept
    {
        return this->type_;
    }

    inline T& GetValue() noexcept
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
    AttributeType type_;

    T value_;
    AttributeBase<T>* reference_ = nullptr;

    // Every reference pointing to this.
    std::vector<AttributeBase<T>*> tracked_references_;
};

class IntWrapper : public AttributeBase<int>
{
public:
    IntWrapper()
        : AttributeBase(AttributeType::kInt, 0)
    { }

    IntWrapper(int value)
        : AttributeBase(AttributeType::kInt, value)
    { }

    inline operator int() { return this->GetValue(); }

    inline std::string ToString() noexcept
    {
        return std::to_string(this->GetValue());
    }

private:
    bool LoadValue(const char* value) noexcept;
    bool LoadValue(int value) noexcept;

    bool InitReference(IntWrapper& ref) noexcept;
};

class FloatWrapper : public AttributeBase<float>
{
public:
    FloatWrapper()
        : AttributeBase(AttributeType::kFloat, 0.0f)
    { }

    FloatWrapper(float value)
        : AttributeBase(AttributeType::kFloat, value)
    { }

    operator float() { return this->GetValue(); }

    inline std::string ToString() noexcept
    {
        return std::to_string(this->GetValue());
    }

private:
    bool LoadValue(const char* value) noexcept;
    bool LoadValue(float value) noexcept;

    bool InitReference(FloatWrapper& ref) noexcept;
};

class BoolWrapper : public AttributeBase<bool>
{
public:
    BoolWrapper()
        : AttributeBase(AttributeType::kBool, false)
    { }

    BoolWrapper(bool value)
        : AttributeBase(AttributeType::kBool, value)
    { }

    inline operator bool() { return this->GetValue(); }

    inline std::string ToString() noexcept
    {
        return std::to_string(this->GetValue());
    }

private:
    bool LoadValue(const char* value) noexcept;
    bool LoadValue(bool value) noexcept;

    bool InitReference(BoolWrapper& ref) noexcept;
};

class StringWrapper : public AttributeBase<std::string>
{
public:
    StringWrapper()
        : AttributeBase(AttributeType::kString, std::string())
    { }

    StringWrapper(std::string value)
        : AttributeBase(AttributeType::kString, value)
    { }

    inline operator std::string() { return this->GetValue(); }

    inline std::string ToString() noexcept
    {
        return '"' + this->GetValue() + '"';
    }

private:
    bool LoadValue(const char* value) noexcept;

    bool InitReference(StringWrapper& ref) noexcept;
};

struct InternalVector2
{
    InternalVector2()
        : x(0), y(0)
    { }
    InternalVector2(float x, float y)
        : x(x), y(y)
    { }

    FloatWrapper x, y;
};

class Vector2Wrapper : public AttributeBase<InternalVector2>
{
public:
    Vector2Wrapper()
        : AttributeBase(AttributeType::kVector2, InternalVector2())
    { }

    Vector2Wrapper(float x, float y)
        : AttributeBase(AttributeType::kVector2, InternalVector2(x, y))
    { }

    Vector2Wrapper(Vector2 value)
        : AttributeBase(AttributeType::kVector2,
                        InternalVector2(value.x, value.y))
    { }

    inline operator Vector2()
    {
        InternalVector2& ref = this->GetValue();
        return Vector2(ref.x, ref.y);
    }

    inline std::string ToString() noexcept
    {
        InternalVector2& val = this->GetValue();
        return std::to_string(val.x) + "," +
               std::to_string(val.y);
    }

private:
    bool LoadValue(Vector2 value) noexcept;

    bool InitReference(Vector2Wrapper& ref) noexcept;
};

struct InternalVector4
{
    InternalVector4()
        : x(0), y(0), z(0), w(0)
    { }
    InternalVector4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w)
    { }

    FloatWrapper x, y, z, w;
};

class Vector4Wrapper : public AttributeBase<InternalVector4>
{
public:
    Vector4Wrapper()
        : AttributeBase(AttributeType::kVector4, InternalVector4())
    { }

    Vector4Wrapper(float x, float y, float z, float w)
        : AttributeBase(AttributeType::kVector4, InternalVector4(x, y, z, w))
    { }

    Vector4Wrapper(Vector4 value)
        : AttributeBase(AttributeType::kVector4,
                        InternalVector4(value.x, value.y, value.z, value.w))
    { }

    inline operator Vector4()
    {
        InternalVector4& ref = this->GetValue();
        return Vector4(ref.x, ref.y, ref.z, ref.w);
    }

    inline std::string ToString() noexcept
    {
        InternalVector4& val = this->GetValue();
        return std::to_string(val.x) + "," +
               std::to_string(val.y) + "," +
               std::to_string(val.z) + "," +
               std::to_string(val.w);
    }

private:
    bool LoadValue(Vector4 value) noexcept;

    bool InitReference(Vector4Wrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ATTRIBUTE_TYPES_H_

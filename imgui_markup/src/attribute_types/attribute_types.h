#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPES_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPES_H_

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

static std::string AttributeTypeToString(AttributeType type);

// Forward declaration for references
class IntWrapper;
class FloatWrapper;
class BoolWrapper;
class StringWrapper;
class Vector2Wrapper;
class Vector4Wrapper;
class InternalVector2;
class InternalVector4;

struct AttributeInterface
{
    inline virtual AttributeType GetType() const noexcept = 0;

    inline virtual std::string ToString() noexcept = 0;

    virtual void Reset() noexcept = 0;

    bool LoadValue(AttributeInterface& ref) noexcept;
    virtual bool LoadValue(int value) noexcept { return false; };
    virtual bool LoadValue(float value) noexcept { return false; };
    virtual bool LoadValue(bool value) noexcept { return false; };
    virtual bool LoadValue(std::string value) noexcept { return false; };

    virtual bool LoadValue(InternalVector2& value) noexcept { return false; };
    virtual bool LoadValue(InternalVector4& value) noexcept { return false; };

    bool InitReference(AttributeInterface& ref) noexcept;
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

    void Reset() noexcept
    {
        if (this->reference_ != nullptr)
            this->reference_->RemoveTrackedReference(this);

        this->reference_ = nullptr;
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

    void RemoveTrackedReference(AttributeBase<T>* ref)
    {
        for (unsigned int i = 0; i < this->tracked_references_.size(); i++)
        {
            if (this->tracked_references_[i] == ref)
            {
                this->tracked_references_.erase(
                    this->tracked_references_.begin() + i);
            }
        }
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

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPES_H_

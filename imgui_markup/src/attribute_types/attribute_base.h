#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_BASE_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_BASE_H_

/**
 * @file attribute_base.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains base classes used internally by the markup languages
 *        attribute types.
 * @copyright Copyright (c) 2022
 */

#include <string>  // std::string
#include <map>     // std::map

namespace igm::internal
{

enum class AttributeType
{
    kInt,
    kFloat,
    kBool,
    kString,
    kVector2,
    kVector4,
    kPadding,
    kMargin,
    kColor,

    // Enums
    kOrientation
};

class IntWrapper;
class FloatWrapper;
class BoolWrapper;
class StringWrapper;
class Vector2Wrapper;
class Vector4Wrapper;
class PaddingWrapper;
class MarginWrapper;
class ColorWrapper;
class OrientationWrapper;

class AttributeInterface
{
public:
    inline virtual AttributeType GetType() const noexcept = 0;
    inline virtual std::string GetName() const noexcept = 0;

    inline virtual std::string ToString() const noexcept = 0;

    inline virtual AttributeInterface* GetReference() const noexcept = 0;

    inline virtual AttributeInterface* GetChildAttribute(std::string name)
        const noexcept = 0;

    /**
     * Is the value set through the markup language?
     */
    inline virtual bool IsValueSet() const noexcept = 0;

    virtual void Reset() noexcept = 0;

private:
    friend class Interpreter;

    /**
     * Set the is_value_set variable to true.
     * Implemented by AttributeBase and used by the interpreter.
     */
    inline virtual void EnableIsValueSet() noexcept = 0;

    bool LoadValue(const AttributeInterface& val) noexcept;
    virtual bool LoadValue(const IntWrapper& val) noexcept { return false; }
    virtual bool LoadValue(const FloatWrapper& val) noexcept { return false; }
    virtual bool LoadValue(const BoolWrapper& val) noexcept { return false; }
    virtual bool LoadValue(const StringWrapper& val) noexcept { return false; }
    virtual bool LoadValue(const Vector2Wrapper& val) noexcept { return false; }
    virtual bool LoadValue(const Vector4Wrapper& val) noexcept { return false; }
    virtual bool LoadValue(const PaddingWrapper& val) noexcept { return false; }
    virtual bool LoadValue(const MarginWrapper& val) noexcept { return false; }
    virtual bool LoadValue(const ColorWrapper& val) noexcept { return false; }
    virtual bool LoadValue(const OrientationWrapper& val) noexcept
        { return false; }

    bool InitReference(AttributeInterface& ref) noexcept;
    virtual bool InitReference(IntWrapper& ref) noexcept { return false; }
    virtual bool InitReference(FloatWrapper& ref) noexcept { return false; }
    virtual bool InitReference(BoolWrapper& ref) noexcept { return false; }
    virtual bool InitReference(StringWrapper& ref) noexcept { return false; }
    virtual bool InitReference(Vector2Wrapper& ref) noexcept { return false; }
    virtual bool InitReference(Vector4Wrapper& ref) noexcept { return false; }
    virtual bool InitReference(PaddingWrapper& ref) noexcept { return false; }
    virtual bool InitReference(MarginWrapper& ref) noexcept { return false; }
    virtual bool InitReference(ColorWrapper& ref) noexcept { return false; }
    virtual bool InitReference(OrientationWrapper& ref) noexcept
        { return false; }
};

template<typename T>
class AttributeBase : public AttributeInterface
{
public:
    AttributeBase(AttributeType type, T value)
        : type_(type)
    {
        this->SetValue(value);
    }

    virtual ~AttributeBase()
    {
        for (auto* reference : this->tracked_references_)
        {
            if (reference)
                reference->RemoveReference();
        }
    }

    inline AttributeType GetType() const noexcept
    {
        return this->type_;
    }

    inline AttributeInterface* GetReference() const noexcept
    {
        return dynamic_cast<AttributeInterface*>(this->reference_);
    }

    AttributeInterface* GetChildAttribute(std::string name) const noexcept
    {
        if (this->child_attributes_mapping_.find(name) ==
            this->child_attributes_mapping_.end())
        {
            return nullptr;
        }

        return this->child_attributes_mapping_.at(name);
    }

    void Reset() noexcept
    {
        if (this->reference_ != nullptr)
            this->reference_->RemoveTrackedReference(this);

        this->reference_ = nullptr;
    }

    inline bool IsValueSet() const noexcept { return this->is_value_set_; }
    inline void EnableIsValueSet() noexcept { this->is_value_set_ = true; }

    inline T GetValue() const noexcept
    {
        if (this->reference_)
        {
            if (this->getting_value_)
                return this->value_;

            this->getting_value_ = true;
            const T value = this->reference_->GetValue();
            this->getting_value_ = false;

            return value;
        }

        return this->value_;
    }

    inline T& GetValueReference() noexcept
    {
        if (this->reference_)
        {
            if (this->getting_value_)
                return this->value_;

            this->getting_value_ = true;
            T& value = this->reference_->GetValueReference();
            this->getting_value_ = false;

            return value;
        }

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
        if (this->reference_)
        {
            this->value_ = this->reference_->GetValue();
            this->reference_->RemoveTrackedReference(this);
        }

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
    void InitChildAttribute(std::string name, AttributeInterface* ref)
    {
        this->child_attributes_mapping_[name] = ref;
    }

    inline void IMPL_InitReference(AttributeBase<T>* reference)
    {
        this->reference_ = reference;
        reference->TrackReference(this);
    }

private:
    AttributeType type_;

    T value_;
    AttributeBase<T>* reference_ = nullptr;

    // Every reference pointing to this attribute.
    std::vector<AttributeBase<T>*> tracked_references_;

    // Mapping of the child attributes that can be accessed
    // through the markup language.
    std::map<std::string, AttributeInterface*> child_attributes_mapping_;

    // Is the value set through the markup language?
    bool is_value_set_ = false;

    // Sets if we are currently in the process of getting the value.
    // Used to detect endless loops in references.
    mutable bool getting_value_ = false;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_BASE_H_

#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INTERNAL_VECTOR_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INTERNAL_VECTOR_H_

#include "attribute_types/float_wrapper.h"

namespace igm::internal
{

struct InternalVector2
{
    InternalVector2()
        : x(0), y(0)
    { }
    InternalVector2(FloatWrapper x, FloatWrapper y)
        : x(x), y(y)
    { }

    FloatWrapper x;
    FloatWrapper y;
};

struct InternalVector4
{
    InternalVector4()
        : x(0), y(0), z(0), w(0)
    { }
    InternalVector4(FloatWrapper x, FloatWrapper y, FloatWrapper z,
                    FloatWrapper w)
        : x(x), y(y), z(z), w(w)
    { }

    FloatWrapper x;
    FloatWrapper y;
    FloatWrapper z;
    FloatWrapper w;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INTERNAL_VECTOR_H_

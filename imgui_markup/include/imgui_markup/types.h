#ifndef IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_TYPES_H_
#define IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_TYPES_H_

/**
 * @file types.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains custom types used by the API.
 * @copyright Copyright (c) 2022
 */

namespace igm
{

struct Vector2
{
    Vector2()
        : x(0), y(0)
    { }
    Vector2(float x, float y)
        : x(x), y(y)
    { }

    float x, y;
};

struct Vector4
{
    Vector4()
        : x(0), y(0), z(0), w(0)
    { }
    Vector4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w)
    { }

    float x, y, z, w;
};

}  // namespace igm

#endif  // IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_TYPES_H_

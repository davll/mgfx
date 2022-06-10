#pragma once

#include "mgfx_types.h"

#if defined(__x86_64__) || defined(_M_X64)
#define MGFX_MATH_SSE
#include <xmmintrin.h>
#endif

namespace mgfx {

//
// Type Definitions
//

union vec3 {
    f32 f[3];
    struct { f32 x, y, z; };
};
static_assert(sizeof(vec3) == 12);
static_assert(offsetof(vec3, f) == 0);
static_assert(offsetof(vec3, x) == 0);
static_assert(offsetof(vec3, y) == 4);
static_assert(offsetof(vec3, z) == 8);

union pos3 {
    f32 f[3];
    struct { f32 x, y, z; };
};
static_assert(sizeof(pos3) == 12);
static_assert(offsetof(pos3, f) == 0);
static_assert(offsetof(pos3, x) == 0);
static_assert(offsetof(pos3, y) == 4);
static_assert(offsetof(pos3, z) == 8);

union vec4 {
    f32 f[4];
    struct {
        union {
            vec3 v;
            struct { f32 x, y, z; };
        };
        f32 w;
    };
};
static_assert(sizeof(vec4) == 16);
static_assert(offsetof(vec4, f) == 0);
static_assert(offsetof(vec4, v) == 0);
static_assert(offsetof(vec4, x) == 0);
static_assert(offsetof(vec4, y) == 4);
static_assert(offsetof(vec4, z) == 8);
static_assert(offsetof(vec4, w) == 12);

union quat {
    f32 f[4];
    struct {
        union {
            vec3 v;
            struct { f32 x, y, z; };
        };
        f32 w;
    };
};
static_assert(sizeof(quat) == 16);
static_assert(offsetof(quat, f) == 0);
static_assert(offsetof(quat, v) == 0);
static_assert(offsetof(quat, x) == 0);
static_assert(offsetof(quat, y) == 4);
static_assert(offsetof(quat, z) == 8);
static_assert(offsetof(quat, w) == 12);

union mat4 {
    f32 f[16];
    vec4 c[4];
    struct { vec4 x, y, z, w; };
};
static_assert(sizeof(mat4) == 64);
static_assert(offsetof(mat4, f) == 0);
static_assert(offsetof(mat4, c) == 0);
static_assert(offsetof(mat4, x) == 0);
static_assert(offsetof(mat4, y) == 16);
static_assert(offsetof(mat4, z) == 32);
static_assert(offsetof(mat4, w) == 48);

//
// Arithmetic Operators
//

inline vec4 operator+(const vec4& a, const vec4& b) noexcept
{
    return { .f = { a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w } };
}

inline vec4 operator*(const vec4& a, f32 s) noexcept
{
    return { .f = { a.x*s, a.y*s, a.z*s, a.w*s } };
}

inline f32 operator*(const vec4& a, const vec4& b) noexcept
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline vec4 operator*(const mat4& a, const vec4& b) noexcept
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline mat4 operator*(const mat4& a, const mat4& b) noexcept
{
    mat4 m;
    for (int i = 0; i < 4; ++i)
        m.c[i] = a * b.c[i];
    return m;
}

}

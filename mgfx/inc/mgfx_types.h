#pragma once

#include <stddef.h>
#include <stdint.h>

namespace mgfx {

//
// Basic Types
//

using i32 = int32_t;
using u32 = uint32_t;
using isize = ptrdiff_t;
using usize = size_t;
using f32 = float;

static_assert(sizeof(isize) == sizeof(usize));
static_assert(sizeof(f32) == 4);

union rgba {
    u32 b;
    uint8_t c[4];
    struct {
        u32 r : 8;
        u32 g : 8;
        u32 b : 8;
        u32 a : 8;
    };
};
static_assert(sizeof(rgba) == 4);
static_assert(alignof(rgba) == 4);

//
// Object Handles
//

#define MGFX_DEFINE_HANDLE(tyname) \
    struct tyname {\
        u32 magic : 16; u32 index : 16; \
        static tyname null() { return { 0, 0 }; } \
        operator bool() const { return !!magic; } \
        bool operator==(tyname o) const { return magic == o.magic && index == o.index; } \
    };

MGFX_DEFINE_HANDLE(HScene)
MGFX_DEFINE_HANDLE(HCamera)

// struct HScene       { u32 magic : 16; u32 index : 16; };
// struct HCamera      { u32 magic : 16; u32 index : 16; };
// struct HLight       { u32 magic : 16; u32 index : 16; };
// struct HEntity      { u32 magic : 16; u32 index : 16; };
// struct HMesh        { u32 magic : 16; u32 index : 16; };
// struct HMaterial    { u32 magic : 16; u32 index : 16; };
// struct HBuffer      { u32 magic : 16; u32 index : 16; };
// struct HTexture     { u32 magic : 16; u32 index : 16; };

#undef MGFX_DEFINE_HANDLE

//
// Interfaces
//

class ISceneManager;
class IMeshManager;
class IMaterialManager;
class IBufferManager;
class ITextureManager;

}

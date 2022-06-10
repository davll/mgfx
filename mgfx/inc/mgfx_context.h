#pragma once

#include "mgfx_types.h"

namespace mgfx {

class IContext {
public:
    virtual ISceneManager* GetSceneManager() = 0;
    // virtual IMeshManager* GetMeshManager() = 0;
    // virtual IMaterialManager* GetMaterialManager() = 0;
    // virtual IBufferManager* GetBufferManager() = 0;
    // virtual ITextureManager* GetTextureManager() = 0;
};

}

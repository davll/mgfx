#pragma once

#include "mgfx_types.h"
#include "mgfx_math.h"

namespace mgfx {

class ISceneManager {
public:

    //
    // Scenes
    //

    virtual HScene CreateScene() = 0;
    virtual void DestroyScene(HScene scn) = 0;

    //
    // Cameras
    //

    virtual void CreateCameras(HScene scn, u32 n,
        _Out_writes_(n) HCamera* cs) = 0;

    // TODO: Update Cameras

    virtual void DeleteCameras(HScene scn, u32 n,
        _In_reads_(n) const HCamera* cs) = 0;

    //
    // Lights
    //

    // virtual void CreateLight(HScene scn, u32 n,
    //     _Out_writes_(n) HLight* ls) = 0;

    // TODO: Update Lights

    // virtual void DeleteLights(HScene scn, u32 n,
    //     _In_reads_(n) const HLight* ls) = 0;

    //
    // Entities
    //

    // virtual void CreateEntities(HScene scn, u32 n,
    //     _Out_writes_(n) HEntity* es) = 0;

    // TODO: Update Entities

    // virtual void DeleteEntities(HScene scn, u32 n,
    //     _In_reads_(n) const HEntity* es) = 0;

    //
    // Debug Drawings
    //

    virtual void DrawLines(HScene scn, u32 n,
        _In_reads_(2*n) const vec3* pts,
        _In_reads_(2*n) const rgba* cols) = 0;
};

}

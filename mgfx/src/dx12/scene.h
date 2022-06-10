#pragma once

#include <mgfx_scene.h>
#include <vector>

namespace mgfx {

struct alignas(16) LineVertex {
    float pos[3];
    uint32_t col;
};

struct Scene {
    HScene self;
    std::vector<LineVertex> debug_lines_vertices;
};

class SceneManager : public ISceneManager {
public:
    SceneManager();
    ~SceneManager();

    //
    // Scenes
    //

    virtual HScene CreateScene() override;
    virtual void DestroyScene(HScene scn) override;

    //
    // Cameras
    //

    virtual void CreateCameras(HScene scn, u32 n,
        _Out_writes_(n) HCamera* cs) override;

    // TODO: Update Cameras

    virtual void DeleteCameras(HScene scn, u32 n,
        _In_reads_(n) const HCamera* cs) override;

    //
    // Debug Drawings
    //

    virtual void DrawLines(HScene scn, u32 n,
        _In_reads_(2*n) const vec3* pts,
        _In_reads_(2*n) const rgba* cols) override;

private:
    bool IsValidScene(HScene scn) const;

private:
    std::vector<Scene> m_Scenes;
    std::vector<HScene> m_FreeList;
};

}

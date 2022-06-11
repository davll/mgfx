#pragma once

#include <mgfx_scene.h>
#include <vector>
#include <deque>
#include <span>

namespace mgfx::dx12 {

struct alignas(16) LineVertex {
    float pos[3];
    uint32_t col;
};

struct Camera {
    HCamera self;
};

struct Scene {
    HScene self;
    std::vector<Camera> m_Cameras;
    std::deque<HCamera> m_FreeCameras;
    std::vector<LineVertex> m_DrawLineVertexList;

    bool IsCamera(HCamera cam) const;

    void CreateCameras(u32 n, HCamera* cs);
    void DeleteCameras(u32 n, const HCamera* cs);

    void ClearDrawLines();
    void AddDrawLines(u32 n, const vec3* pts, const rgba* cols);
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

public:
    bool IsScene(HScene scn) const;
    Scene* GetScene(HScene scn);

private:
    std::vector<Scene> m_Scenes;
    std::deque<HScene> m_FreeScenes;
};

}

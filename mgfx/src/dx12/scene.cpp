#include "scene.h"
#include <assert.h>

namespace mgfx::dx12 {

bool Scene::IsCamera(HCamera cam) const
{
    if (cam.magic == 0)
        return false;
    if (cam.index >= m_Cameras.size())
        return false;
    return m_Cameras[cam.index].self == cam;
}

void Scene::CreateCameras(u32 n, HCamera* cs)
{
    u32 numFree = m_FreeCameras.size();
    u32 numNew = n - std::min(n, numFree);
    u32 base = m_Cameras.size();

    m_Cameras.reserve(base + numNew);
    for (u32 i = 0; i < numNew; ++i) {
        m_Cameras.emplace_back();
    }

    for (u32 i = 0; i < numFree; ++i) {
        HCamera cam = m_FreeCameras.front();
        m_FreeCameras.pop_front();
        cam.update_magic();
        cs[i] = cam;
    }

    for (u32 i = 0; i < numNew; ++i) {
        HCamera cam = HCamera::start(base + i);
        cs[numFree + i] = cam;
    }

    for (u32 i = 0; i < n; ++i) {
        m_Cameras[i].self = cs[i];
    }
}

void Scene::DeleteCameras(u32 n, const HCamera* cs)
{
    for (u32 i = 0; i < n; ++i) {
        assert(IsCamera(cs[i]));
    }

    for (u32 i = 0; i < n; ++i) {
        HCamera cam = cs[i];
        m_Cameras[cam.index].self = HCamera::null();

        m_FreeCameras.push_back(cam);
    }
}

void Scene::ClearDrawLines()
{
    m_DrawLineVertexList.clear();
}

void Scene::AddDrawLines(u32 n, const vec3* pts, const rgba* cols)
{
    size_t off = m_DrawLineVertexList.size();
    m_DrawLineVertexList.reserve(off + n);
    for (u32 i = 0; i < n; ++i) {
        vec3 p = pts[i];
        LineVertex v = {
            .pos = { p.x, p.y, p.z },
            .col = cols[i].b,
        };
        m_DrawLineVertexList.emplace_back(v);
    }
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

HScene SceneManager::CreateScene()
{
    HScene scn;
    if (m_FreeScenes.empty()) {
        scn = HScene::start(m_Scenes.size());
        m_Scenes.emplace_back();
    } else {
        scn = m_FreeScenes.front();
        m_FreeScenes.pop_front();
        scn.update_magic();
    }
    Scene& inst = m_Scenes[scn.index];
    inst.self = scn;
    return scn;
}

void SceneManager::DestroyScene(HScene scn)
{
    assert(IsScene(scn));

    Scene& inst = m_Scenes[scn.index];
    inst.self = HScene::null();
    inst.m_Cameras.clear();
    inst.m_FreeCameras.clear();
    inst.m_DrawLineVertexList.clear();

    m_FreeScenes.push_back(scn);
}

void SceneManager::CreateCameras(HScene scn, u32 n,
    _Out_writes_(n) HCamera* cs)
{
    assert(IsScene(scn));

    Scene& inst = m_Scenes[scn.index];
    inst.CreateCameras(n, cs);
}

void SceneManager::DeleteCameras(HScene scn, u32 n,
    _In_reads_(n) const HCamera* cs)
{
    assert(IsScene(scn));

    Scene& inst = m_Scenes[scn.index];
    inst.DeleteCameras(n, cs);
}

void SceneManager::DrawLines(HScene scn, u32 n,
    _In_reads_(2*n) const vec3* pts,
    _In_reads_(2*n) const rgba* cols)
{
    assert(IsScene(scn));
    assert(pts);
    assert(cols);

    Scene& inst = m_Scenes[scn.index];
    inst.AddDrawLines(n, pts, cols);
}

bool SceneManager::IsScene(HScene scn) const
{
    if (scn.magic == 0)
        return false;
    if (scn.index >= m_Scenes.size())
        return false;
    return m_Scenes[scn.index].self == scn;
}

Scene* SceneManager::GetScene(HScene scn)
{
    assert(IsScene(scn));
    return &m_Scenes[scn.index];
}

}

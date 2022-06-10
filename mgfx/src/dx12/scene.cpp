#include "scene.h"
#include <assert.h>

namespace mgfx {

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

HScene SceneManager::CreateScene()
{
    HScene scn;
    if (m_FreeList.empty()) {
        scn.magic = 0x8000;
        scn.index = m_Scenes.size();
        m_Scenes.emplace_back();
    } else {
        scn = m_FreeList.back();
        scn.magic = (scn.magic + 1) | 0x8000;
        m_FreeList.pop_back();
    }
    Scene& inst = m_Scenes[scn.index];
    inst.self = scn;
    return scn;
}

void SceneManager::DestroyScene(HScene scn)
{
    assert(IsValidScene(scn));

    Scene& inst = m_Scenes[scn.index];
    inst.self = HScene::null();
    inst.debug_lines_vertices.clear();

    m_FreeList.push_back(scn);
}

void SceneManager::DrawLines(HScene scn, u32 n,
    _In_reads_(2*n) const vec3* pts,
    _In_reads_(2*n) const rgba* cols)
{
    assert(IsValidScene(scn));

    Scene& inst = m_Scenes[scn.index];
    inst.debug_lines_vertices.reserve(inst.debug_lines_vertices.size() + n);
}

bool SceneManager::IsValidScene(HScene scn) const
{
    if (scn.magic == 0)
        return false;
    if (scn.index >= m_Scenes.size())
        return false;
    return m_Scenes[scn.index].self == scn;
}

}

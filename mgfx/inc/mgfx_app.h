#pragma once

#include <mgfx.h>
#include <imgui.h>

namespace mgfx {

class IUserData {
public:
    virtual void Initialize(IContext* ctx) = 0;
    virtual void Update() = 0;
    virtual void Shutdown() = 0;
};

struct AppInfo {
    std::string Name;
    IUserData* UserData;
};

}

extern void OpenMgfx(mgfx::AppInfo& info);

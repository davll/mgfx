#include <mgfx.h>
#include <mgfx_app.h>

using namespace mgfx;

struct UserData : public mgfx::IUserData {
    mgfx::IContext* context;
    bool show_demo_window;

    virtual void Initialize(IContext* ctx) override;
    virtual void Update() override;
    virtual void Shutdown() override;
};

void OpenMgfx(mgfx::AppInfo& info)
{
    info.Name = "Hello World";
    info.UserData = new UserData();
}

void UserData::Initialize(IContext* ctx)
{
    this->context = ctx;
    this->show_demo_window = true;
    // SPDLOG_INFO("Called InitUserData");
}

void UserData::Update()
{
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }
    // SPDLOG_INFO("Called UpdateUserData");
}

void UserData::Shutdown()
{
    delete this;
    // SPDLOG_INFO("Called DeinitUserData");
}

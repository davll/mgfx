#include <mgfx.h>
#include <mgfx_app.h>

using namespace mgfx;

struct UserData : public mgfx::IUserData {
    mgfx::IContext* context;
    mgfx::HScene scene;
    mgfx::HCamera camera;

    virtual void Initialize(IContext* ctx) override;
    virtual void Update() override;
    virtual void Shutdown() override;
};

void OpenMgfx(mgfx::AppInfo& info)
{
    info.Name = "Simple Lines";
    info.UserData = new UserData();
}

void UserData::Initialize(IContext* ctx)
{
    this->context = ctx;

    auto sceneMgr = ctx->GetSceneManager();
    this->scene = sceneMgr->CreateScene();
    sceneMgr->CreateCameras(this->scene, 1, &this->camera);
    // SPDLOG_INFO("Called InitUserData");
}

void UserData::Update()
{
    auto sceneMgr = context->GetSceneManager();

    const int n = 2;
    mgfx::vec3 points[n*2] = {
        { .f = { -0.5f, -0.5f, 0.0f } },
        { .f = {  0.5f,  0.5f, 0.0f } },
        { .f = { -0.5f,  0.5f, 0.0f } },
        { .f = {  0.5f, -0.5f, 0.0f } },
    };
    mgfx::rgba colors[n*2] = {
        { .c = { 255, 255, 0, 255 } },
        { .c = { 0, 255, 0, 255 } },
        { .c = { 255, 0, 0, 255 } },
        { .c = { 0, 0, 255, 255 } },
    };

    sceneMgr->DrawLines(scene, n, points, colors);

    // SPDLOG_INFO("Called UpdateUserData");
}

void UserData::Shutdown()
{
    auto sceneMgr = context->GetSceneManager();
    sceneMgr->DeleteCameras(scene, 1, &camera);
    sceneMgr->DestroyScene(scene);

    delete this;
    // SPDLOG_INFO("Called DeinitUserData");
}

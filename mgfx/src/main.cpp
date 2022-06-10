#include <mgfx.h>
#include <mgfx_app.h>
#include "config.h"
#include <SDL.h>
#include <SDL_main.h>
#include <CLI11.hpp>

// TODO: switch backends
#include "dx12/context.h"

int main(int argc, char* argv[])
{
    //
    // Setup UserData
    //
    mgfx::AppInfo info;
    OpenMgfx(info);

    //
    // Parse Arguments
    //
    {
        for (int i = 0; i < argc; ++i) {
            SPDLOG_DEBUG("ARGV[{}] = {}", i, argv[i]);
        }

        CLI::App app("Micro Graphics Lib");

        std::string configFile;
        app.add_option("-c,--config", configFile, "Config File");

        try {
            app.parse(argc, argv);
        } catch (const CLI::ParseError& e) {
            return app.exit(e);
        }
    }

    // TODO: Load Config
    // Perhaps JSON format

    //
    // Initialize
    //
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SPDLOG_ERROR("Unable to initialize SDL: {}", SDL_GetError());
        return 1;
    }
    auto context = new mgfx::dx12::Context();
    info.UserData->Initialize(context);

    //
    // Looping
    //
    while (!context->ShouldQuit()) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            context->ProcessEvent(event);
        }
        if (context->ShouldQuit())
            break;

        if (context->BeginFrame()) {
            info.UserData->Update();
            context->EndFrame();
        }
    }

    //
    // Shutdown
    //
    info.UserData->Shutdown();
    delete context;
    SDL_Quit();

    return 0;
}

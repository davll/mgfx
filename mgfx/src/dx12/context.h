#pragma once

#include <mgfx_context.h>
#include "common.h"
#include <SDL.h>
#include <imgui.h>

namespace mgfx::dx12 {

class Device;
class SwapChain;
class GpuDescriptorHeap;

class Context : public IContext {
public:
    virtual ISceneManager* GetSceneManager() override;

public:
    Context();
    ~Context();
    bool ShouldQuit() const;
    bool ProcessEvent(const SDL_Event& event);
    bool ProcessImGuiEvent(const SDL_Event& event);
    bool ProcessWindowEvent(const SDL_Event& event);
    bool BeginFrame();
    void EndFrame();
    
    static IDXGIFactory6* CreateFactory();
    static IDXGIAdapter4* ChooseAdapter(IDXGIFactory6* factory);

private:
    bool m_Quit;
    SDL_Window* m_Window;
    Uint32 m_WindowID;
    ImGuiContext* m_ImGuiCtx;

    Device* m_Device;
    SwapChain* m_SwapChain;
    GpuDescriptorHeap* m_ResourceDescriptorHeap;
    GpuDescriptorHeap* m_SamplerDescriptorHeap;

    //
    // Current Frame
    //
    ID3D12Resource* m_FinalTexture;
    D3D12_CPU_DESCRIPTOR_HANDLE m_FinalRenderTargetView;
    ID3D12GraphicsCommandList* m_CommandList;
};

}

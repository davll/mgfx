#include "swap_chain.h"
#include <SDL.h>
#include <SDL_syswm.h>

namespace mgfx::dx12 {

SwapChain::SwapChain(const CreateInfo& info)
: m_NumFrames(info.NumFrames)
, m_WorkIds((size_t)info.NumFrames, 0)
, m_CommandQueue(info.CommandQueue)
, m_BackBuffers((size_t)info.NumFrames)
{
    MGFX_DX12_CHKHR(
        m_CommandQueue->GetCommandQueue()->GetDevice(IID_PPV_ARGS(&m_Device))
    );

    Init(info);
}

SwapChain::~SwapChain()
{
    WaitAll();
    delete m_Fence;
    m_RenderTargetViewHeap->Release();
    ClearBuffers();
    m_SwapChain->Release();
    m_CommandQueue = NULL;
    m_Device->Release();
}

void SwapChain::Present()
{
    UINT prevBufferIdx = m_SwapChain->GetCurrentBackBufferIndex();

    MGFX_DX12_CHKHR(
        m_SwapChain->Present(1, 0)
    );

    UINT64 workId = m_CommandQueue->SubmitSignal(m_Fence);
    m_WorkIds[prevBufferIdx] = workId;

    //workId = m_WorkIds[m_SwapChain->GetCurrentBackBufferIndex()];
    //Wait(workId);
}

void SwapChain::Resize()
{
    WaitAll();
    ClearBuffers();
    m_SwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
    SetupBuffers();
    WriteDescriptors();
}

void SwapChain::Wait(UINT64 workId)
{
    m_Fence->CpuWait(workId);
}

void SwapChain::WaitAll()
{
    m_Fence->CpuWait();
}

void SwapChain::Init(const CreateInfo& info)
{
    int width, height;
    SDL_GetWindowSize(info.Window, &width, &height);

    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    if (SDL_GetWindowWMInfo(info.Window, &wminfo) == 0) {
        SPDLOG_ERROR("Unable to get SDL WMInfo");
        abort();
    }
    HWND hwnd = wminfo.info.win.window;

    DXGI_SWAP_CHAIN_DESC1 desc;
    desc.Width = width;
    desc.Height = height;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Stereo = FALSE;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount = m_NumFrames;
    desc.Scaling = DXGI_SCALING_NONE;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    desc.Flags = 0;

    ID3D12CommandQueue* commandQueue = info.CommandQueue->GetCommandQueue();

    IDXGISwapChain1* swapChain1;
    MGFX_DX12_CHKHR(
        info.Factory->CreateSwapChainForHwnd(commandQueue, hwnd, &desc, NULL, NULL, &swapChain1)
    );

    IDXGISwapChain3* swapChain3;
    MGFX_DX12_CHKHR(
        swapChain1->QueryInterface(IID_PPV_ARGS(&swapChain3))
    );
    swapChain1->Release();
    m_SwapChain = swapChain3;

    m_Fence = new CommandFence({
        m_Device,
        TRUE,
    });

    InitDescriptorHeap();
    SetupBuffers();
    WriteDescriptors();
}

void SwapChain::InitDescriptorHeap()
{
    {
        D3D12_DESCRIPTOR_HEAP_DESC desc;
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        desc.NumDescriptors = m_NumFrames;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        desc.NodeMask = 0;

        MGFX_DX12_CHKHR(
            m_Device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_RenderTargetViewHeap))
        );
    }

    m_RenderTargetViewDescriptorSize = m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    m_RenderTargetViewBase = m_RenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();
}

void SwapChain::WriteDescriptors()
{
    D3D12_RENDER_TARGET_VIEW_DESC desc;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipSlice = 0;
    desc.Texture2D.PlaneSlice = 0;

    D3D12_CPU_DESCRIPTOR_HANDLE handle = m_RenderTargetViewBase;
    UINT size = m_RenderTargetViewDescriptorSize;
    for (UINT i = 0; i < m_NumFrames; ++i, handle.ptr += size) {
        m_Device->CreateRenderTargetView(m_BackBuffers[i], &desc, handle);
    }
}

void SwapChain::SetupBuffers()
{
    for (UINT i = 0; i < m_NumFrames; ++i) {
        ID3D12Resource* buffer;
        MGFX_DX12_CHKHR(
            m_SwapChain->GetBuffer(i, IID_PPV_ARGS(&buffer))
        );
        m_BackBuffers[i] = buffer;
    }
}

void SwapChain::ClearBuffers()
{
    for (UINT i = 0; i < m_NumFrames; ++i) {
        m_BackBuffers[i]->Release();
        m_BackBuffers[i] = NULL;
    }
}

}

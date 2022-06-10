#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>
#include <spdlog/spdlog.h>
#include <span>

#define MGFX_DX12_CHKHR(hr) do { if (FAILED(hr)) { abort(); } } while(0)

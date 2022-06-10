project(mgfx)

set(HDR_FILES
    inc/mgfx.h
    inc/mgfx_types.h
    inc/mgfx_math.h
    inc/mgfx_app.h
    inc/mgfx_context.h
    inc/mgfx_scene.h
)

set(SRC_FILES
    src/config.h
    src/mgfx.cpp
    src/main.cpp
)

set(SRC_DX12_FILES
    src/dx12/command_fence.h
    src/dx12/command_fence.cpp
    src/dx12/command_pool.h
    src/dx12/command_pool.cpp
    src/dx12/command_queue.h
    src/dx12/command_queue.cpp
    src/dx12/common.h
    src/dx12/context.h
    src/dx12/context.cpp
    src/dx12/descriptor_span.h
    src/dx12/device.h
    src/dx12/device.cpp
    src/dx12/gpu_descriptor_heap.h
    src/dx12/gpu_descriptor_heap.cpp
    src/dx12/scene.h
    src/dx12/scene.cpp
    src/dx12/swap_chain.h
    src/dx12/swap_chain.cpp
)

add_library(mgfx STATIC
    ${HDR_FILES}
    ${SRC_FILES}
    ${SRC_DX12_FILES}
)
target_include_directories(mgfx PUBLIC inc)
target_link_libraries(mgfx
PUBLIC
    spdlog
    imgui 
PRIVATE
    json
    SDL2::SDL2
    SDL2::SDL2main
    imgui-sdl2
    imgui-dx12
    d3d12
    dxgi
    CLI11
)

cmake_minimum_required(VERSION 3.31)
project(imgui_application)

set(CMAKE_CXX_STANDARD 17)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)

set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
        ${IMGUI_DIR}/backends/imgui_impl_dx11.cpp
)

set(SOURCES
        App.cpp
        App.h
        ImGuiManager.cpp
        ImGuiManager.h
        main.cpp
        IUIComponent.h)

add_executable(imgui_application
        ${SOURCES}
        ${IMGUI_SOURCES})

target_include_directories(imgui_application PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

target_link_libraries(imgui_application
        d3d11
        dxgi
        dxguid
        d3dcompiler
        user32
        dwmapi
)
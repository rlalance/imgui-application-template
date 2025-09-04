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
        Core/App.cpp
        Core/App.h
        Core/ImGuiManager.cpp
        Core/ImGuiManager.h
        main.cpp
        Core/AbstractUIComponent.h
        Multithreading/AsyncTaskManager.cpp
        Multithreading/AsyncTaskManager.h
        Multithreading/Examples/MultithreadingExamples.cpp
        Multithreading/Examples/MultithreadingExamples.h
        DungeonGenerator/DungeonGenerator.cpp
        DungeonGenerator/DungeonGenerator.h
        DungeonGenerator/MyApp.cpp
        DungeonGenerator/MyApp.h
        DungeonGenerator/MainWindowComponent.cpp
        DungeonGenerator/MainWindowComponent.h
        Core/CacheSystem/HugeObjectCache.cpp
        Core/CacheSystem/HugeObjectCache.h
        Core/CacheSystem/CacheItemPolicy.cpp
        Core/CacheSystem/CacheItemPolicy.h
        Core/CacheSystem/CacheItem.cpp
        Core/CacheSystem/CacheItem.h)

add_executable(imgui_application
        ${SOURCES}
        ${IMGUI_SOURCES})

target_include_directories(imgui_application PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${CMAKE_SOURCE_DIR}/Core
        ${CMAKE_SOURCE_DIR}/Core/CacheSystem
        ${CMAKE_SOURCE_DIR}/Multithreading
        ${CMAKE_SOURCE_DIR}/DungeonGenerator
)


target_link_libraries(imgui_application
        d3d11
        dxgi
        dxguid
        d3dcompiler
        user32
        dwmapi
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(my_tests Tests/CacheItemTests.cpp)

target_include_directories(my_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/Core
        ${CMAKE_SOURCE_DIR}/Core/CacheSystem
        ${CMAKE_SOURCE_DIR}/Multithreading
        ${CMAKE_SOURCE_DIR}/DungeonGenerator
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

target_link_libraries(my_tests PRIVATE gtest_main)
add_test(NAME MyCacheTests COMMAND my_tests)

# Enable CTest
enable_testing()
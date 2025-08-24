#pragma once

#include <d3d11.h>
#include <windows.h>
#include <functional>

class ImGuiManager
{
public:
    ImGuiManager(int width, int height, const wchar_t* title);
    ~ImGuiManager();

    // Runs the main loop, calling the provided render function each frame
    void run(const std::function<void()>& renderFunc);

    HWND getHwnd() const { return hwnd; }

private:
    HWND hwnd = nullptr;
    WNDCLASSEXW wc = {};
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    IDXGISwapChain* swapChain = nullptr;
    ID3D11RenderTargetView* renderTargetView = nullptr;
    UINT resizeWidth_ = 0, resizeHeight = 0;
    bool swapChainOccluded = false;

    static LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
    bool createDeviceD3D(HWND hWnd);
    void cleanupDeviceD3D();
    void createRenderTarget();
    void cleanupRenderTarget();
};

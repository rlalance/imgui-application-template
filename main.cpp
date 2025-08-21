#include "App.h"
#include "ImGuiManager.h"


int main()
{
    ImGuiManager imgui(1280, 800, L"Supply Chain Example");
    App app;

    imgui.run([&app]()
    {
        app.draw();

        if (app.shouldExit())
        {
            PostQuitMessage(0);
        }
    });

    return 0;
}


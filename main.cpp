#include "Core/ImGuiManager.h"
#include "DungeonGenerator/MyApp.h"

int main()
{
    ImGuiManager imgui(1280, 800, L"Wave Collapse Based Dungeon Generator");
    MyApp app;

    imgui.run([&]()
    {
        app.Draw();
    });

    return 0;
}

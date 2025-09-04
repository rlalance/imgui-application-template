#include "Core/ImGuiManager.h"
#include "DungeonGenerator/MyApp.h"

int main()
{
    ImGuiManager imgui(1920, 1080, L"Wave Collapse Based Dungeon Generator");
    MyApp app;

    imgui.run([&]()
    {
        app.Update();
        app.Draw();
    });

    return 0;
}

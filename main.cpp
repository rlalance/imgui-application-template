#include "App.h"
#include "imgui.h"
#include "ImGuiManager.h"
#include "IUIComponent.h"

// Example component that implements IUIComponent
class MainWindowComponent : public IUIComponent
{
public:
    void Draw() override
    {
        ImGui::Begin("Main Window");
        ImGui::Text("Main Window Component Example");
        ImGui::End();
    }
};

class MyApp : public App
{
};

int main()
{
    ImGuiManager imgui(1280, 800, L"ImGui Application");
    MyApp app;

    app.AddComponent("Main", std::make_unique<MainWindowComponent>());

    imgui.run([&app]()
    {
        app.Draw();

        if (app.shouldExit())
        {
            PostQuitMessage(0);
        }
    });

    return 0;
}


#include <future>

#include "App.h"
#include "imgui.h"
#include "ImGuiManager.h"
#include "AbstractUIComponent.h"
#include "Multithreading/AsyncTaskManager.h"
#include "Multithreading/Examples/MultithreadingExamples.h"

// Example component that implements IUIComponent
class MainWindowComponent : public AbstractUIComponent
{
public:
    void Draw() override
    {
        if (mVisible)
        {
            ImGui::Begin("Main Window", &mVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
            ImGui::Text("Main Window Component Example");
            ImGui::End();
        }
    }
};

class MyApp : public App
{
public:
    void DrawMainMenuBar() override
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                {
                    mExit = true;
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About"))
                {
                    mShowAbout = true;
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    };
};

int main()
{
    ImGuiManager imgui(1280, 800, L"ImGui Application");
    MyApp app;
    AsyncTaskManager taskManager;

    auto future_str = taskManager.submitTask(&MultithreadingExamples::generate_fibonacci, 400);
    auto future_pi = taskManager.submitTask(&MultithreadingExamples::calculate_pi_chudnovsky, 100000);

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


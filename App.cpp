#include "App.h"
#include "imgui/imgui.h"

void App::Draw()
{
    DrawMainMenuBar();
    DrawAboutWindow();
    DrawComponents();
}

void App::DrawAboutWindow()
{
    if (mShowAbout)
    {
        ImGui::OpenPopup("AboutPopup");
        mShowAbout = false;
    }

    if (ImGui::BeginPopupModal("AboutPopup", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("ImGui Application Template\n\nBuilt with Dear ImGui.");
        if (ImGui::Button("OK")) ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
}

void App::DrawMainMenuBar()
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
}

void App::DrawComponents()
{
    for (auto& [name, window] : mComponents)
    {
        if (window)
        {
            window->Draw();
        }
    }
}

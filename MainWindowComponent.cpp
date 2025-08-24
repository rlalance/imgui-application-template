#include "MainWindowComponent.h"

void MainWindowComponent::Draw()
{
    if (mVisible)
    {
        ImGui::Begin("Main Window", &mVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Main Window Component Example");

        if (ImGui::Button("Generate Dungeon"))
        {
            if (onDungeonGenerationButtonClicked)
                onDungeonGenerationButtonClicked();
        }

        ImGui::End();
    }
}

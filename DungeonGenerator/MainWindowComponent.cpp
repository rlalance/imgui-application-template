#include "imgui.h"

#include "MainWindowComponent.h"

void MainWindowComponent::Draw()
{
    if (mVisible)
    {
        ImGui::Begin("Main Window", &mVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Main Window Component Example");

        // Put a slider to adjust grid size and cell size
        ImGui::SliderInt("Grid Size", &mGridSize, 10, 200);
        ImGui::SliderInt("Tile Size", &mTileSize, 10, 50);

        if (ImGui::Button("Generate Dungeon"))
        {
            if (onDungeonGenerationButtonClicked)
                onDungeonGenerationButtonClicked();
        }

        ImGui::End();
    }
}

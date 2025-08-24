#pragma once

#include "../Core/App.h"
#include "../Core/ImGuiManager.h"
#include "DungeonGenerator.h"
#include "MainWindowComponent.h"
#include "../Multithreading/AsyncTaskManager.h"

class MyApp : public App
{
public:
    MyApp();
    void StartDungeonGeneration();
    void DrawDungeonGrid() const;

    void Draw() override;
    void DrawMainMenuBar() override;;

private:
    AsyncTaskManager taskManager;
    bool dungeonGenerationRequested = false;
    std::unique_ptr<DungeonGenerator> generator = std::make_unique<DungeonGenerator>(20, 20);
    bool mShowActivityIndicator = false;
};

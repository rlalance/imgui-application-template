#pragma once

#include "../Core/App.h"
#include "DungeonGenerator.h"
#include "../Multithreading/AsyncTaskManager.h"

class MyApp : public App
{
public:
    MyApp();
    void DrawDungeonGrid() const;
    void Draw() override;
    void DrawMainMenuBar() override;;

    void SetTileSize(float size) { mTileSize = size; }
    float GetTileSize() const { return mTileSize; }

private:
    AsyncTaskManager taskManager;
    bool dungeonGenerationRequested = false;
    std::unique_ptr<DungeonGenerator> generator;
    bool mShowActivityIndicator = false;
    int mGridSize = 100;
    int mTileSize = 20;
};

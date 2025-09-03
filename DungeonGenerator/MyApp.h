#pragma once

#include "AsyncTaskManager.h"
#include "DungeonGenerator.h"

#include <App.h>
#include <CacheSystem/HugeObjectCache.h>

class MyApp : public App
{
public:
    MyApp();
    void DrawDungeonGrid() const;
    void Draw() override;
    void DrawMainMenuBar() override;;

    void SetTileSize(int size) { mTileSize = size; }
    int GetTileSize() const { return mTileSize; }

private:
    AsyncTaskManager taskManager;
    HugeObjectCache cacheSystem;
    bool dungeonGenerationRequested = false;
    std::unique_ptr<DungeonGenerator> generator;
    bool mShowActivityIndicator = false;
    int mGridSize = 100;
    int mTileSize = 20;
};

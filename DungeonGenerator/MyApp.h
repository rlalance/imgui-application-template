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
    void Update();
    void Draw() override;
    void DrawMainMenuBar() override;


    void SetTileSize(int size) { mTileSize = size; }
    int GetTileSize() const { return mTileSize; }

private:
    AsyncTaskManager mTaskManager;
    HugeObjectCache mCacheSystem;
    bool mDungeonGenerationRequested = false;
    std::unique_ptr<DungeonGenerator> mGenerator;
    bool mShowActivityIndicator = false;
    int mGridSize = 100;
    int mTileSize = 20;
};

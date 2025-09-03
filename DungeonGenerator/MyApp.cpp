#include "MyApp.h"

#include "imgui.h"
#include "MainWindowComponent.h"

MyApp::MyApp() : cacheSystem(512), mGridSize(100), mTileSize(20.0f)
{
    generator = std::make_unique<DungeonGenerator>(mGridSize, mGridSize);

    auto mainWindowComponent = std::make_unique<MainWindowComponent>();

    mainWindowComponent->mGridSize = mGridSize;
    mainWindowComponent->mTileSize = mTileSize;

    mainWindowComponent->onDungeonGenerationButtonClicked = [&]() { dungeonGenerationRequested = true; };

    mainWindowComponent->onDungeonGenerationStarted = [&]() { mShowActivityIndicator = true; };

    mainWindowComponent->onDungeonGenerationCompleted = [&]() { mShowActivityIndicator = false; };

    AddComponent("Main", std::move(mainWindowComponent));
}

void MyApp::Draw()
{
    App::Draw();

    auto mainWindowComponent = dynamic_cast<MainWindowComponent&>(GetComponent("Main"));

    if (mGridSize != mainWindowComponent.mGridSize)
    {
        mGridSize = mainWindowComponent.mGridSize;
        generator = std::make_unique<DungeonGenerator>(mGridSize, mGridSize);
    }

    mTileSize = mainWindowComponent.mTileSize;

    if (dungeonGenerationRequested)
    {
        dungeonGenerationRequested = false;
        auto future = taskManager.submitTask([&]()
        {
            auto mainWindow = dynamic_cast<MainWindowComponent&>(GetComponent("Main"));

            mainWindow.onDungeonGenerationStarted();
            generator->GenerateDungeon();
            mainWindow.onDungeonGenerationCompleted();
        });
    }

    DrawDungeonGrid();
}

void MyApp::DrawDungeonGrid() const
{
    const auto& grid = generator->GetGrid();
    ImGui::Begin("Dungeon Grid");
    const ImVec2 spacing = {1, 1};
    ImVec2 cursor = ImGui::GetCursorScreenPos();

    for (int y = 0; y < grid.size(); ++y)
    {
        for (int x = 0; x < grid[y].size(); ++x)
        {
            ImColor tileColor;

            switch (grid[y][x].finalType)
            {
            case TileType::Wall:
                tileColor = ImColor(0.2f, 0.2f, 0.2f, 1.0f); // Dark gray
                break;
            case TileType::Floor:
                tileColor = ImColor(0.8f, 0.8f, 0.8f, 1.0f); // Light gray
                break;
            case TileType::Corridor:
                tileColor = ImColor(0.6f, 0.6f, 0.6f, 1.0f); // Medium gray
                break;
            case TileType::Corner:
                tileColor = ImColor(0.4f, 0.4f, 0.4f, 1.0f); // Slightly darker gray
                break;
            default:
                tileColor = ImColor(0.0f, 0.0f, 0.0f, 1.0f); // Black for unknown
                break;
            }

            ImGui::GetWindowDrawList()->AddRectFilled(
                ImVec2(cursor.x + x * (mTileSize + spacing.x), cursor.y + y * (mTileSize + spacing.y)),
                ImVec2(cursor.x + x * (mTileSize + spacing.x) + mTileSize,
                       cursor.y + y * (mTileSize + spacing.y) + mTileSize),
                tileColor
            );
        }
    }

    ImGui::End();
}

void MyApp::DrawMainMenuBar()
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

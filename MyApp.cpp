#include "MyApp.h"

MyApp::MyApp()
{
    auto main_window_component = std::make_unique<MainWindowComponent>();

    main_window_component->onDungeonGenerationButtonClicked = [&]()
    {
        dungeonGenerationRequested = true;
    };

    main_window_component->onDungeonGenerationStarted = [&]()
    {
        mShowActivityIndicator = true;
    };

    main_window_component->onDungeonGenerationCompleted = [&]()
    {
        mShowActivityIndicator = false;
    };

    AddComponent("Main", std::move(main_window_component));
}

void MyApp::Draw()
{
    App::Draw();

    if (dungeonGenerationRequested)
    {
        dungeonGenerationRequested = false;
        StartDungeonGeneration();
    }

    DrawDungeonGrid();
}

void MyApp::StartDungeonGeneration()
{
    auto future = taskManager.submitTask([&]()
    {
        auto mainWindow = dynamic_cast<MainWindowComponent&>(GetComponent("Main"));

        if (mainWindow.onDungeonGenerationStarted)
        {
            mainWindow.onDungeonGenerationStarted();
        }

        generator->GenerateDungeon();

        if (mainWindow.onDungeonGenerationCompleted)
        {
            mainWindow.onDungeonGenerationCompleted();
        }
    });
}

void MyApp::DrawDungeonGrid() const
{
    // Display the generated dungeon grid
    const auto& grid = generator->GetGrid();
    ImGui::Begin("Dungeon Grid");

    for (const auto& row : grid)
    {
        for (const auto& tile : row)
        {
            char tileChar = ' ';
            switch (tile.finalType)
            {
            case TileType::Wall: tileChar = '#';
                break;
            case TileType::Floor: tileChar = '.';
                break;
            case TileType::Corridor: tileChar = '=';
                break;
            case TileType::Corner: tileChar = '+';
                break;
            default: tileChar = ' ';
                break;
            }
            ImGui::Text("%c", tileChar);
            ImGui::SameLine();
        }
        ImGui::NewLine();
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

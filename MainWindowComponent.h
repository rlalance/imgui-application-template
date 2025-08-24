#pragma once

#include "AbstractUIComponent.h"
#include "imgui.h"

#include <functional>

// Example component that implements IUIComponent
class MainWindowComponent final : public AbstractUIComponent
{
public:
    void Draw() override;

    std::function<void()> onDungeonGenerationButtonClicked;
    std::function<void()> onDungeonGenerationStarted;
    std::function<void()> onDungeonGenerationCompleted;
};

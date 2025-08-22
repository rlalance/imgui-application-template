#pragma once
#include "AbstractUIComponent.h"

#include <map>
#include <memory>
#include <string>

class App
{
public:
    virtual ~App() = default;
    virtual void Draw();
    virtual void DrawMainMenuBar();
    virtual void DrawAboutWindow();

    [[nodiscard]] bool shouldExit() const { return mExit; }

    void AddComponent(const std::string& name, std::unique_ptr<AbstractUIComponent> component)
    {
        mComponents[name] = std::move(component);
    }

    void RemoveComponent(const std::string& name)
    {
        mComponents.erase(name);
    }

private:
    virtual void DrawComponents();
    std::pmr::map<std::string, std::unique_ptr<AbstractUIComponent>> mComponents;

    bool mShowAbout = false;
    bool mExit = false;
};

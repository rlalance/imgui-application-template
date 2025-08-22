#pragma once

class AbstractUIComponent
{
public:
    explicit AbstractUIComponent(const bool visible = true) : mVisible(visible) {}
    virtual ~AbstractUIComponent() = default;

    virtual void Draw() = 0;

    bool IsVisible() const { return mVisible; }
    void Show() { mVisible = true; }
    void Hide() { mVisible = false; }
    void ToggleVisibility() { mVisible = !mVisible; }
    void SetVisibility(const bool visible) { mVisible = visible; }

protected:
    bool mVisible;
};

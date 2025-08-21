#pragma once

class IUIComponent
{
public:
    virtual ~IUIComponent() = default;
    virtual void Draw() = 0;
};

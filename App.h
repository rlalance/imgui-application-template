#pragma once

class App
{
public:
    void DrawMainMenuBar();
    void DrawAboutWindow();

    void draw();
    bool shouldExit() const { return mExit; }

private:
    bool mShowAbout = false;
    bool mExit = false;
};

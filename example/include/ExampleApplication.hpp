#pragma once

#include "ImGuiApplication.hpp"

namespace example
{

class ExampleApplication:
    public fw::ImGuiApplication
{
public:
    ExampleApplication();
    virtual ~ExampleApplication();

protected:
    virtual void onCreate() override;
    virtual void onDestroy() override;
    virtual void onUpdate(
        const std::chrono::high_resolution_clock::duration& deltaTime
    ) override;
    virtual void onRender() override;

    virtual void onMouseButton(int button, int action, int mods) override;
    virtual void onScroll(double xoffset, double yoffset) override;
    virtual void onKey(int key, int scancode, int action, int mods) override;
    virtual void onChar(unsigned int c) override;
};

}

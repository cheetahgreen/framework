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
};

}

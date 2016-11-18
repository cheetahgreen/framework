#pragma once

#include "OpenGLApplication.hpp"

namespace fw
{

class ImGuiApplication:
    public OpenGLApplication
{
public:
    ImGuiApplication();
    virtual ~ImGuiApplication();

protected:
    virtual void onCreate();
    virtual void onDestroy();
    virtual void onUpdate(
        const std::chrono::high_resolution_clock::duration& deltaTime
    );
    virtual void onRender();
};

}

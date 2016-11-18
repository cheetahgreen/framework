#include "ImGuiApplication.hpp"

#include "imgui.h"
#include "ImGuizmo.h"
#include "ImGuiBinding.hpp"

namespace fw
{

ImGuiApplication::ImGuiApplication()
{
}

ImGuiApplication::~ImGuiApplication()
{
}

void ImGuiApplication::onCreate()
{
    OpenGLApplication::onCreate();
    ImGuiBinding::initialize(_window, false);
}

void ImGuiApplication::onDestroy()
{
    ImGuiBinding::shutdown();
    OpenGLApplication::onDestroy();
}

void ImGuiApplication::onUpdate(
    const std::chrono::high_resolution_clock::duration& deltaTime
)
{
    OpenGLApplication::onUpdate(deltaTime);
    ImGuiBinding::newFrame();
    ImGuizmo::BeginFrame();
}

void ImGuiApplication::onRender()
{
    OpenGLApplication::onRender();
    ImGui::Render();
}

}

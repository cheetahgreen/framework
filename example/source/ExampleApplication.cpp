#include "ExampleApplication.hpp"
#include "imgui.h"

namespace example
{

ExampleApplication::ExampleApplication()
{
}

ExampleApplication::~ExampleApplication()
{
}

void ExampleApplication::onCreate()
{
    ImGuiApplication::onCreate();
}

void ExampleApplication::onDestroy()
{
    ImGuiApplication::onDestroy();
}

void ExampleApplication::onUpdate(
    const std::chrono::high_resolution_clock::duration& deltaTime
)
{
    ImGuiApplication::onUpdate(deltaTime);

    if (ImGui::Begin("Example window"))
    {
        ImGui::Text("This is an example window");
    }
    ImGui::End();
}

void ExampleApplication::onRender()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGuiApplication::onRender();
}

}

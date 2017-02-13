#include "Application.hpp"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "fw/DebugShapes.hpp"
#include "fw/TextureUtils.hpp"
#include "fw/Resources.hpp"

#include "Resources.hpp"

namespace application
{

Application::Application():
    _enableCameraRotations{false},
    _cameraRotationSensitivity{0.2, 0.2},
    _showTexturesInspector{false},
    _showImGuiDemo{false}
{
}

Application::~Application()
{
}

void Application::onCreate()
{
    ImGuiApplication::onCreate();

    _phongEffect = std::make_shared<fw::TexturedPhongEffect>();
    _phongEffect->create();

    _universalPhongEffect = std::make_shared<fw::UniversalPhongEffect>();

    _grid = std::make_shared<fw::Grid>(
        glm::ivec2{32, 32},
        glm::vec2{0.5f, 0.5f}
    );

    _frameMarker = std::make_shared<fw::FrameMarker>();

    _textureManager = std::make_shared<fw::TextureManager>();
    _textureManager->setResourcesDirectory(fw::getFrameworkResourcePath(""));

    _textureManagerInspector = std::make_shared<fw::TextureManagerInspector>(
        std::static_pointer_cast<fw::ITextureManagerWithInspection>(
            _textureManager
        )
    );

    _staticModelFactory = std::make_shared<fw::StaticModelFactory>(
        std::static_pointer_cast<fw::ITextureManager>(_textureManager)
    );

    _staticModel = _staticModelFactory->load(
        getApplicationResourcesPath("models/Nanosuit/nanosuit.obj")
    );

    _testTexture = _textureManager->loadTexture(
        fw::getFrameworkResourcePath("textures/wefi_cat.jpg")
    );

    _testTexture2 = _textureManager->loadTexture(
        fw::getFrameworkResourcePath("textures/checker-base.png")
    );

    updateProjectionMatrix();
}

void Application::onDestroy()
{
    ImGuiApplication::onDestroy();
}

void Application::onUpdate(
    const std::chrono::high_resolution_clock::duration& deltaTime
)
{
    ImGuiApplication::onUpdate(deltaTime);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Inspectors"))
        {
            ImGui::MenuItem("Textures", nullptr, &_showTexturesInspector);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Helpers"))
        {
            ImGui::MenuItem("ImGui Test Window", nullptr, &_showImGuiDemo);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    _textureManagerInspector->show(_showTexturesInspector);

    if (_showImGuiDemo)
    {
        ImGui::ShowTestWindow(&_showImGuiDemo);
    }
}

void Application::onRender()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    _phongEffect->begin();
    _phongEffect->setProjectionMatrix(_projectionMatrix);
    _phongEffect->setViewMatrix(_camera.getViewMatrix());
    _phongEffect->setModelMatrix({});
    _grid->render();
    _phongEffect->end();

    glm::mat4 scale = glm::scale({}, glm::vec3{0.1f, 0.1f, 0.1f});
    for (const auto& chunk: _staticModel->getGeometryChunks())
    {
        _universalPhongEffect->setLightDirection({-1, 1, 0});

        _universalPhongEffect->setSolidColor(glm::vec3{});

        _universalPhongEffect->setDiffuseTextureColor(
            chunk.getMaterial()->getAlbedoColor()
        );

        _universalPhongEffect->setDiffuseTexture(
            chunk.getMaterial()->getAlbedoMap()
        );

        _universalPhongEffect->begin();
        _universalPhongEffect->setProjectionMatrix(_projectionMatrix);
        _universalPhongEffect->setViewMatrix(_camera.getViewMatrix());
        _universalPhongEffect->setModelMatrix(chunk.getModelMatrix() * scale);
        chunk.getMesh()->render();
        _universalPhongEffect->end();
    }

    ImGuiApplication::onRender();
}

bool Application::onMouseButton(int button, int action, int mods)
{
    if (ImGuiApplication::onMouseButton(button, action, mods)) { return true; }

    if (GLFW_MOUSE_BUTTON_LEFT == button)
    {
        _enableCameraRotations = GLFW_PRESS == action;
    }

    return true;
}

bool Application::onMouseMove(glm::dvec2 newPosition)
{
    if (ImGuiApplication::onMouseMove(newPosition)) { return true; }

    if (_enableCameraRotations)
    {
        auto movement = getMouseMovement() * _cameraRotationSensitivity;
        _camera.rotate(movement.y, movement.x);
    }

    return true;
}

bool Application::onScroll(double xoffset, double yoffset)
{
    if (fw::ImGuiApplication::onScroll(xoffset, yoffset))
        return true;

    const double cMinimumDistance = 1.0;
    const double cMaximumDistance = 10.0;
    const double cZoomStep = 0.5;
    auto currentDistance = _camera.getDist();
    _camera.setDist(
        std::min(
            std::max(currentDistance + cZoomStep * yoffset, cMinimumDistance),
            cMaximumDistance
        )
    );

    return true;
}

bool Application::onResize()
{
    updateProjectionMatrix();
    return true;
}

void Application::updateProjectionMatrix()
{
    auto windowSize = getWindowSize();
    auto aspectRatio = static_cast<float>(windowSize.x) / windowSize.y;
    _projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.5f, 100.0f);
}

}

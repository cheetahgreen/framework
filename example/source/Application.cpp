#include "Application.hpp"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "fw/DebugShapes.hpp"
#include "fw/TextureUtils.hpp"
#include "fw/Resources.hpp"

#include "fw/components/Transform.hpp"
#include "fw/rendering/Light.hpp"
#include "fw/cameras/ProjectionCamera.hpp"

#include "engine/scripts/ScriptCollection.hpp"
#include "engine/scripts/cameras/FirstPersonCameraScript.hpp"

#include "Resources.hpp"

namespace application
{

using StaticModelHandle = std::shared_ptr<fw::StaticModel>;

Application::Application():
    _entities{_events},
    _systems{_entities, _events},
    _enableCameraRotations{false},
    _showTexturesInspector{false},
    _showImGuiDemo{false},
    _cameraRotationSensitivity{0.2, 0.2}
{
}

Application::~Application()
{
}

void Application::onCreate()
{
    ImGuiApplication::onCreate();

    _windowProperties = std::make_shared<ee::WindowProperties>();
    _windowProperties->setWindowSize(getWindowSize());
    _windowProperties->setFramebufferSize(getFramebufferSize());

    _keyboardInput = std::make_shared<fw::GenericKeyboardInput>();
    _mouseInput = std::make_shared<fw::GenericMouseInput>();

    _universalPhongEffect = std::make_shared<fw::UniversalPhongEffect>();

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

    _testEntity = _entities.create();
    _testEntity.assign_from_copy<StaticModelHandle>(_staticModel);
    _testEntity.assign_from_copy<fw::Transform>(fw::Transform{
        glm::translate({}, glm::vec3{0.0f, 10.0f, 0.0f})
    });

    glm::mat4 viewMtx = glm::lookAt(
        glm::vec3{3.0f, 1.0f, 3.0f},
        glm::vec3{0.0f, 0.0f, 0.0f},
        glm::vec3{0.0f, 1.0f, 0.0f}
    );

    auto cameraScript = std::make_shared<ee::FirstPersonCameraScript>();

    _cameraEntity = _entities.create();
    _cameraEntity.assign<fw::Transform>(glm::inverse(viewMtx));
    _cameraEntity.assign<ee::ScriptCollection>(
        std::vector<std::shared_ptr<ee::IScript>>
        {
            std::static_pointer_cast<ee::IScript>(cameraScript)
        }
    );
    _cameraEntity.assign<fw::ProjectionCamera>();

    _renderingSystem = std::make_shared<ee::ForwardRenderingSystem>();
    _scriptExecutionSystem = std::make_shared<ee::ScriptExecutionSystem>(
        std::static_pointer_cast<ee::IWindowProperties>(_windowProperties),
        std::static_pointer_cast<fw::IKeyboardInput>(_keyboardInput),
        std::static_pointer_cast<fw::IMouseInput>(_mouseInput)
    );

    _systems.add<ee::ForwardRenderingSystem>(_renderingSystem);
    _systems.add<ee::ScriptExecutionSystem>(_scriptExecutionSystem);

    _systems.configure();
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

    _systems.update<ee::ScriptExecutionSystem>(entityx::TimeDelta{});
    _systems.update<ee::ForwardRenderingSystem>(entityx::TimeDelta{});

    ImGuiApplication::onRender();

    _keyboardInput->nextFrame();
    _mouseInput->nextFrame();
}

bool Application::onMouseButton(int button, int action, int mods)
{
    if (ImGuiApplication::onMouseButton(button, action, mods)) { return true; }

    if (action == GLFW_PRESS)
    {
        _mouseInput->buttonDown(button);
    }
    else if (action == GLFW_RELEASE)
    {
        _mouseInput->buttonUp(button);
    }

    return true;
}

bool Application::onMouseMove(glm::dvec2 newPosition)
{
    if (ImGuiApplication::onMouseMove(newPosition)) { return true; }
    _mouseInput->move(newPosition);
    return true;
}

bool Application::onScroll(double xoffset, double yoffset)
{
    if (fw::ImGuiApplication::onScroll(xoffset, yoffset))
        return true;

    return true;
}

bool Application::onKey(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        _keyboardInput->keyDown(key);
    }
    else if (action == GLFW_RELEASE)
    {
        _keyboardInput->keyUp(key);
    }

    return true;
}

bool Application::onResize()
{
    _windowProperties->setWindowSize(getWindowSize());
    _windowProperties->setFramebufferSize(getFramebufferSize());
    return true;
}

}

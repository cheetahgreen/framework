#include "Application.hpp"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "fw/DebugShapes.hpp"
#include "fw/TextureUtils.hpp"
#include "fw/Resources.hpp"

#include "fw/components/Transform.hpp"
#include "fw/components/EntityInfo.hpp"
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
    _cameraRotationSensitivity{0.2, 0.2},
    _vfsInspector{_virtualFilesystem}
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

    _virtualFilesystem.addDirectory(fw::getFrameworkResourcePath(""), "fw");
    _virtualFilesystem.addDirectory(getApplicationResourcesPath(""), "app");

    auto defaultFramebuffer = std::make_shared<fw::DefaultFramebuffer>(*this);
    _defaultFramebuffer = std::static_pointer_cast<fw::IFramebuffer>(
        defaultFramebuffer
    );

    _framebuffer = std::make_shared<fw::Framebuffer>(glm::ivec2{800, 600});

    _keyboardInput = std::make_shared<fw::GenericKeyboardInput>();
    _mouseInput = std::make_shared<fw::GenericMouseInput>();

    _textureManager = std::make_shared<fw::TextureManager>(_virtualFilesystem);
    _textureManager->setResourcesDirectory(fw::getFrameworkResourcePath(""));

    auto texMgrInspection =
        std::static_pointer_cast<fw::ITextureManagerWithInspection>(
            _textureManager
        );

    _textureManagerInspector = std::make_shared<fw::TextureManagerInspector>(
        texMgrInspection
    );

    _staticModelFactory = std::make_shared<fw::StaticModelFactory>(
        _virtualFilesystem,
        std::static_pointer_cast<fw::ITextureManager>(_textureManager)
    );

    _sceneInspector = std::make_shared<ee::SceneInspector>(
        _virtualFilesystem,
        texMgrInspection,
        _staticModelFactory,
        &_entities
    );

    _renderingSystem = std::make_shared<ee::ForwardRenderingSystem>();
    _scriptExecutionSystem = std::make_shared<ee::ScriptExecutionSystem>(
        std::static_pointer_cast<ee::IWindowProperties>(_windowProperties),
        std::static_pointer_cast<fw::IKeyboardInput>(_keyboardInput),
        std::static_pointer_cast<fw::IMouseInput>(_mouseInput)
    );

    _systems.add<ee::ForwardRenderingSystem>(_renderingSystem);
    _systems.add<ee::ScriptExecutionSystem>(_scriptExecutionSystem);
    _systems.configure();

    createCamera();
    createTestEntity();
    createLight();

    auto envTexture = _textureManager->loadTexture(
        "/app/textures/newport_loft.hdr"
    );

    _equirectCubemapConv =
        std::make_unique<fw::EquirectangularToCubemapConverter>(envTexture);

    std::shared_ptr<fw::Cubemap> cubemap = _equirectCubemapConv->generate(
        {512, 512}
    );

    fw::DiffuseIrradianceCubemapGenerator diffIrrGen(cubemap);
    std::shared_ptr<fw::Cubemap> irradianceCubemap = diffIrrGen.generate(
        {512, 512}
    );

    _renderingSystem->setSkybox(cubemap);
    _renderingSystem->setIrradianceMap(irradianceCubemap);
}

void Application::createCamera()
{
    auto cameraScript = std::make_shared<ee::FirstPersonCameraScript>();
    cameraScript->getController().setPosition({0.2f, 0.14f, 0.65f});

    _cameraEntity = _entities.create();
    _cameraEntity.assign<fw::EntityInfo>("Default camera");
    _cameraEntity.assign<fw::Transform>(glm::mat4{});
    _cameraEntity.assign<ee::ScriptCollection>(
        std::vector<std::shared_ptr<ee::IScript>>
        {
            std::static_pointer_cast<ee::IScript>(cameraScript)
        }
    );

    _cameraEntity.assign<fw::ProjectionCamera>();
}

void Application::createTestEntity()
{
    _staticModel = _staticModelFactory->load(
        "/app/models/Cerberus/Cerberus.obj"
    );

    _testEntity = _entities.create();
    _testEntity.assign<fw::EntityInfo>("Cerberus PBR");
    _testEntity.assign<fw::RenderMesh>(_staticModel);
    _testEntity.assign_from_copy<fw::Transform>(fw::Transform{
        glm::translate({}, glm::vec3{0.0f, 0.0f, 0.0f})
    });

    fw::Material material;

    material.AlbedoMap = _textureManager->loadTexture(
        "/app/models/Cerberus/Textures/Cerberus_A.png"
    );

    material.NormalMap = _textureManager->loadTexture(
        "/app/models/Cerberus/Textures/Cerberus_N.png"
    );

    material.MetalnessMap = _textureManager->loadTexture(
        "/app/models/Cerberus/Textures/Cerberus_M.png"
    );

    material.RoughnessMap = _textureManager->loadTexture(
        "/app/models/Cerberus/Textures/Cerberus_R.png"
    );

    _testEntity.assign_from_copy<fw::Material>(material);
}

void Application::createLight()
{
    auto lightEntity = _entities.create();
    lightEntity.assign<fw::EntityInfo>("Default light");
    lightEntity.assign<fw::Transform>(glm::translate(
        glm::mat4{},
        glm::vec3{1.25f, 1.0f, 0.0f}
    ));
    lightEntity.assign<fw::Light>(fw::Light{
        fw::LightType::Point,
        glm::vec3{1.0f, 1.0f, 1.0f},
        100.0f
    });
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
    _perfMon.startFrame();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Inspectors"))
        {
            ImGui::MenuItem(
                "Content",
                nullptr,
                &_vfsInspector.getShowFlag()
            );

            ImGui::MenuItem(
                "Scene",
                nullptr,
                &_sceneInspector->getShowFlag()
            );

            ImGui::MenuItem(
                "Textures",
                nullptr,
                &_showTexturesInspector
            );

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Helpers"))
        {
            ImGui::MenuItem("ImGui Test Window", nullptr, &_showImGuiDemo);
            ImGui::EndMenu();
        }

        ImGui::Text("FPS: %d", _perfMon.getLastFPS());

        ImGui::EndMainMenuBar();
    }

    _textureManagerInspector->show(_showTexturesInspector);
    _sceneInspector->show();
    _vfsInspector.show();

    if (_showImGuiDemo)
    {
        ImGui::ShowTestWindow(&_showImGuiDemo);
    }
}

void Application::onRender()
{
    _renderingSystem->setFramebuffer(_framebuffer);

    _systems.update<ee::ScriptExecutionSystem>(entityx::TimeDelta{});
    _systems.update<ee::ForwardRenderingSystem>(entityx::TimeDelta{});

    if (ImGui::Begin(
        "Render window",
        nullptr,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar
    ))
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::BeginMenu("Size"))
                {
                    ImGui::MenuItem(
                        "Fit to image without scaling",
                        nullptr,
                        false,
                        false
                    );

                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        auto maxSize = ImGui::GetContentRegionAvail();
        auto rtSize = _framebuffer->getSize();
        glm::vec2 finalSize{rtSize.x, rtSize.y};

        if (maxSize.x < finalSize.x)
        {
            auto scaleFactor = maxSize.x / finalSize.x;
            finalSize.x = maxSize.x;
            finalSize.y *= scaleFactor;
        }

        if (maxSize.y < finalSize.y)
        {
            auto scaleFactor = maxSize.y / finalSize.y;
            finalSize.y = maxSize.y;
            finalSize.x *= scaleFactor;
        }

        glm::vec2 totalMargin{
            maxSize.x - finalSize.x,
            maxSize.y - finalSize.y
        };

        auto currentCursorPos = ImGui::GetCursorPos();
        ImGui::SetCursorPos({
            currentCursorPos.x + totalMargin.x / 2,
            currentCursorPos.y + totalMargin.y / 2
        });

        ImGui::ImageButton(
            reinterpret_cast<void*>(_framebuffer->getColorTexture()),
            ImVec2{finalSize.x, finalSize.y},
            ImVec2{0.0f, 1.0f},
            ImVec2{1.0f, 0.0f},
            0
        );

        if (ImGui::IsItemActive())
        {
            ImGui::CaptureKeyboardFromApp(false);
        }

        if (ImGui::IsItemHovered())
        {
            ImGui::CaptureMouseFromApp(false);
        }
    }
    ImGui::End();

    _defaultFramebuffer->use();
    auto windowFramebufferSize = _defaultFramebuffer->getSize();
    glViewport(0, 0, windowFramebufferSize.x, windowFramebufferSize.y);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

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
    if (fw::ImGuiApplication::onKey(key, scancode, action, mods))
    {
        return true;
    }

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

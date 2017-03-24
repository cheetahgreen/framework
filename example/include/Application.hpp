#pragma once

#include <memory>

#include "glm/glm.hpp"
#include "entityx/entityx.h"

#include "fw/ImGuiApplication.hpp"
#include "fw/UniversalPhongEffect.hpp"
#include "fw/inputs/GenericKeyboardInput.hpp"
#include "fw/inputs/GenericMouseInput.hpp"
#include "fw/models/StaticModel.hpp"
#include "fw/models/StaticModelFactory.hpp"
#include "fw/resources/TextureManager.hpp"
#include "fw/editor/TextureManagerInspector.hpp"

#include "engine/editor/SceneInspector.hpp"
#include "engine/info/WindowProperties.hpp"
#include "engine/rendering/ForwardRenderingSystem.hpp"
#include "engine/scripts/ScriptExecutionSystem.hpp"

namespace application
{

class Application:
    public fw::ImGuiApplication
{
public:
    Application();
    virtual ~Application();

protected:
    virtual void onCreate() override;
    void createCamera();
    void createTestEntity();
    void createLight();

    virtual void onDestroy() override;
    virtual void onUpdate(
        const std::chrono::high_resolution_clock::duration& deltaTime
    ) override;
    virtual void onRender() override;

    virtual bool onMouseButton(int button, int action, int mods) override;
    virtual bool onMouseMove(glm::dvec2 newPosition) override;
    virtual bool onScroll(double xoffset, double yoffset) override;
    virtual bool onKey(int key, int scancode, int action, int mods) override;
    virtual bool onResize() override;

private:
    entityx::EventManager _events;
    entityx::EntityManager _entities;
    entityx::SystemManager _systems;

    entityx::Entity _testEntity;
    entityx::Entity _cameraEntity;

    std::shared_ptr<fw::StaticModel> _staticModel;

    bool _enableCameraRotations;
    bool _showTexturesInspector;
    bool _showImGuiDemo;

    std::shared_ptr<fw::TextureManager> _textureManager;
    std::shared_ptr<fw::StaticModelFactory> _staticModelFactory;

    std::shared_ptr<fw::TextureManagerInspector> _textureManagerInspector;
    std::shared_ptr<ee::SceneInspector> _sceneInspector;

    std::shared_ptr<fw::GenericKeyboardInput> _keyboardInput;
    std::shared_ptr<fw::GenericMouseInput> _mouseInput;

    std::shared_ptr<ee::WindowProperties> _windowProperties;
    std::shared_ptr<ee::ForwardRenderingSystem> _renderingSystem;
    std::shared_ptr<ee::ScriptExecutionSystem> _scriptExecutionSystem;

    glm::dvec2 _cameraRotationSensitivity;
};

}

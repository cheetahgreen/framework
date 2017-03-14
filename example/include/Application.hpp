#pragma once

#include <memory>

#include "glm/glm.hpp"
#include "entityx/entityx.h"

#include "fw/FrameMarker.hpp"
#include "fw/Grid.hpp"
#include "fw/ImGuiApplication.hpp"
#include "fw/Mesh.hpp"
#include "fw/OrbitingCamera.hpp"
#include "fw/TexturedPhongEffect.hpp"
#include "fw/UniversalPhongEffect.hpp"
#include "fw/Vertices.hpp"
#include "fw/models/StaticModel.hpp"
#include "fw/models/StaticModelFactory.hpp"
#include "fw/resources/TextureManager.hpp"
#include "fw/editor/TextureManagerInspector.hpp"
#include "fw/rendering/ForwardRenderingSystem.hpp"

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
    virtual void onDestroy() override;
    virtual void onUpdate(
        const std::chrono::high_resolution_clock::duration& deltaTime
    ) override;
    virtual void onRender() override;

    virtual bool onMouseButton(int button, int action, int mods) override;
    virtual bool onMouseMove(glm::dvec2 newPosition) override;
    virtual bool onScroll(double xoffset, double yoffset) override;
    virtual bool onResize() override;

    void updateProjectionMatrix();

private:
    entityx::EventManager _events;
    entityx::EntityManager _entities;
    entityx::SystemManager _systems;

    entityx::Entity _testEntity;
    entityx::Entity _cameraEntity;

    std::shared_ptr<fw::StaticModel> _staticModel;

    std::shared_ptr<fw::TexturedPhongEffect> _phongEffect;
    std::shared_ptr<fw::UniversalPhongEffect> _universalPhongEffect;

    std::shared_ptr<fw::Grid> _grid;
    std::shared_ptr<fw::FrameMarker> _frameMarker;

    std::shared_ptr<fw::Material> _materialOverride;

    glm::mat4 _projectionMatrix;

    bool _enableCameraRotations;
    bool _showTexturesInspector;
    bool _showImGuiDemo;

    std::shared_ptr<fw::TextureManager> _textureManager;
    std::shared_ptr<fw::TextureManagerInspector> _textureManagerInspector;
    std::shared_ptr<fw::StaticModelFactory> _staticModelFactory;

    std::shared_ptr<fw::ForwardRenderingSystem> _renderingSystem;

    glm::dvec2 _cameraRotationSensitivity;
};

}

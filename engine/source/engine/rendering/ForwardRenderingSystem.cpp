#include "engine/rendering/ForwardRenderingSystem.hpp"

#include <stdexcept>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "fw/DebugShapes.hpp"
#include "fw/cameras/ProjectionCamera.hpp"
#include "fw/components/Transform.hpp"
#include "fw/models/StaticModel.hpp"
#include "fw/rendering/Light.hpp"

#include "engine/internal/Logging.hpp"

namespace ee
{

using StaticModelHandle = std::shared_ptr<fw::StaticModel>;

ForwardRenderingSystem::ForwardRenderingSystem()
{
    _universalPhongEffect = std::make_shared<fw::UniversalPhongEffect>();
    _box = fw::createBox({0.01f, 0.01f, 0.01f});
}

ForwardRenderingSystem::~ForwardRenderingSystem()
{
}

void ForwardRenderingSystem::update(
    entityx::EntityManager &entities,
    entityx::EventManager& events,
    entityx::TimeDelta
)
{
    if (!_framebuffer)
    {
        LOG(ERROR) << "Framebuffer is not set.";
        throw std::logic_error("Framebuffer is not set.");
    }

    _framebuffer->use();
    auto framebufferSize = _framebuffer->getSize();
    auto aspectRatio =
        static_cast<double>(framebufferSize.x) / framebufferSize.y;

    glViewport(0, 0, framebufferSize.x, framebufferSize.y);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glm::mat4 viewMatrix{};
    glm::mat4 projectionMatrix{};

    entities.each<fw::Transform, fw::ProjectionCamera>(
        [&viewMatrix, &projectionMatrix, aspectRatio](
            entityx::Entity entity,
            fw::Transform& transform,
            fw::ProjectionCamera& camera
        )
        {
            viewMatrix = glm::inverse(transform.getTransform());
            projectionMatrix = camera.getProjectionMatrix(aspectRatio);
        }
    );

    fw::Transform currentLightTransform;
    fw::Light currentLight;

    entities.each<fw::Transform, fw::Light>(
        [&currentLightTransform, &currentLight](
            entityx::Entity entity,
            fw::Transform& transform,
            fw::Light& light
        )
        {
            currentLight = light;
            currentLightTransform = transform;
        }
    );

    entityx::ComponentHandle<fw::Transform> transformation;
    entityx::ComponentHandle<fw::Light> light;
    entityx::ComponentHandle<StaticModelHandle> staticModel;

    for (auto entity:
            entities.entities_with_components(transformation, staticModel))
    {
        auto material = entity.component<fw::Material>();
        for (const auto& chunk: (*staticModel)->getGeometryChunks())
        {
            _universalPhongEffect->setLight(
                currentLightTransform,
                currentLight
            );

            _universalPhongEffect->setMaterial(*material);

            _universalPhongEffect->begin();
            _universalPhongEffect->setProjectionMatrix(projectionMatrix);
            _universalPhongEffect->setViewMatrix(viewMatrix);
            _universalPhongEffect->setModelMatrix(
                transformation->getTransform()
            );

            chunk.getMesh()->render();

            _universalPhongEffect->end();
        }
    }

    for (auto entity:
            entities.entities_with_components(transformation, light))
    {
        _universalPhongEffect->setSolidColor(glm::vec3{});
        _universalPhongEffect->setEmissionColor(light->getColor());
        _universalPhongEffect->setDiffuseTextureColor(glm::vec4{});
        _universalPhongEffect->begin();
        _universalPhongEffect->setProjectionMatrix(projectionMatrix);
        _universalPhongEffect->setViewMatrix(viewMatrix);
        _universalPhongEffect->setModelMatrix(transformation->getTransform());
        _box->render();
        _universalPhongEffect->end();
    }
}

}
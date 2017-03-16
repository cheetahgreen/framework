#include "engine/rendering/ForwardRenderingSystem.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "fw/cameras/ProjectionCamera.hpp"
#include "fw/components/Transform.hpp"
#include "fw/models/StaticModel.hpp"

namespace ee
{

using StaticModelHandle = std::shared_ptr<fw::StaticModel>;

ForwardRenderingSystem::ForwardRenderingSystem()
{
    _universalPhongEffect = std::make_shared<fw::UniversalPhongEffect>();
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
    glm::mat4 viewMatrix{};
    glm::mat4 projectionMatrix{};

    entities.each<fw::Transform, fw::ProjectionCamera>(
        [&viewMatrix, &projectionMatrix](
            entityx::Entity entity,
            fw::Transform& transform,
            fw::ProjectionCamera& camera
        )
        {
            viewMatrix = glm::inverse(transform.getTransform());
            projectionMatrix = camera.getProjectionMatrix();
        }
    );

    entityx::ComponentHandle<fw::Transform> transformation;
    entityx::ComponentHandle<StaticModelHandle> staticModel;

    for (auto entity:
            entities.entities_with_components(transformation, staticModel))
    {
        glm::mat4 scale = glm::scale({}, glm::vec3{0.1f, 0.1f, 0.1f});
        for (const auto& chunk: (*staticModel)->getGeometryChunks())
        {
            _universalPhongEffect->setLightDirection(glm::normalize(
                glm::vec3{-1, 0, -2}
            ));

            _universalPhongEffect->setSolidColor(glm::vec3{});

            _universalPhongEffect->setDiffuseTextureColor(
                chunk.getMaterial()->getAlbedoColor()
            );

            _universalPhongEffect->setDiffuseTexture(
                chunk.getMaterial()->getAlbedoMap()
            );

            _universalPhongEffect->setNormalMap(
                chunk.getMaterial()->getNormalMap()
            );

            _universalPhongEffect->begin();
            _universalPhongEffect->setProjectionMatrix(projectionMatrix);
            _universalPhongEffect->setViewMatrix(viewMatrix);
            _universalPhongEffect->setModelMatrix(
                transformation->getTransform() * scale
            );

            chunk.getMesh()->render();

            _universalPhongEffect->end();
        }
    }
}

}

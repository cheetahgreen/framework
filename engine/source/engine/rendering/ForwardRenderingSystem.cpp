#include "engine/rendering/ForwardRenderingSystem.hpp"

#include <stdexcept>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "fw/DebugShapes.hpp"
#include "fw/cameras/ProjectionCamera.hpp"
#include "fw/components/Transform.hpp"
#include "fw/models/StaticModel.hpp"
#include "fw/models/RenderMesh.hpp"
#include "fw/Resources.hpp"

#include "fw/rendering/Light.hpp"
#include "fw/rendering/AreaLight.hpp"

#include "engine/internal/Logging.hpp"

namespace ee
{

using StaticModelHandle = std::shared_ptr<fw::StaticModel>;

ForwardRenderingSystem::ForwardRenderingSystem()
{
    _universalPhongEffect = std::make_shared<fw::UniversalPhongEffect>();
    _box = fw::createBox({0.01f, 0.01f, 0.01f});
    _skybox = fw::createBox({1.0f, 1.0f, 1.0f});
    _plane = fw::createPlane(1.0f, 1.0f);

    _skyboxShader = std::make_shared<fw::ShaderProgram>(
        fw::getFrameworkResourcePath("shaders/Skybox.sbl")
    );

    _skyboxViewLoc = _skyboxShader->getUniformLoc("view");
    _skyboxProjLoc = _skyboxShader->getUniformLoc("projection");
    _skyboxLoc = _skyboxShader->getUniformLoc("skyboxCube");
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

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

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
    entityx::ComponentHandle<fw::AreaLight> areaLight;
    entityx::ComponentHandle<fw::RenderMesh> renderMesh;

    for (auto entity:
            entities.entities_with_components(transformation, renderMesh))
    {
        auto staticModel = renderMesh->getMesh();
        auto material = entity.component<fw::Material>();
        for (const auto& chunk: staticModel->getGeometryChunks())
        {
            _universalPhongEffect->setLight(
                currentLightTransform,
                currentLight
            );

            _universalPhongEffect->setMaterial(*material);
            _universalPhongEffect->setIrradianceMap(_irradianceMap);
            _universalPhongEffect->setPrefilterMap(_prefilterMap);
            _universalPhongEffect->setBrdfLut(_brdfLut);

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

    for (auto entity:
            entities.entities_with_components(transformation, areaLight))
    {
        _universalPhongEffect->setSolidColor(glm::vec3{});
        _universalPhongEffect->setEmissionColor(areaLight->color);
        _universalPhongEffect->setDiffuseTextureColor(glm::vec4{});
        _universalPhongEffect->begin();
        _universalPhongEffect->setProjectionMatrix(projectionMatrix);
        _universalPhongEffect->setViewMatrix(viewMatrix);

        auto areaLightSizeMat = glm::scale(
            glm::mat4{},
            glm::vec3{areaLight->size.x, 0.0f, areaLight->size.y}
        );

        _universalPhongEffect->setModelMatrix(
            transformation->getTransform() * areaLightSizeMat
        );

        _plane->render();
        _universalPhongEffect->end();
    }

    if (_cubemap)
    {
        glDepthFunc(GL_LEQUAL);
        _skyboxShader->use();
        _skyboxShader->setUniform(_skyboxViewLoc, viewMatrix);
        _skyboxShader->setUniform(_skyboxProjLoc, projectionMatrix);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemap->getId());

        _skybox->render();

        glDepthFunc(GL_LESS);
    }
}

}

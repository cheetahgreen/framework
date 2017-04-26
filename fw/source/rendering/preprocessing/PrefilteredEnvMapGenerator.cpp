#include "fw/rendering/preprocessing/PrefilteredEnvMapGenerator.hpp"
#include "fw/Resources.hpp"

namespace fw
{

PrefilteredEnvMapGenerator::PrefilteredEnvMapGenerator(
    std::shared_ptr<Cubemap> environmentCubemap
):
    _environmentCubemap{environmentCubemap}
{
    _shaderProgram = std::make_shared<ShaderProgram>(
        getFrameworkResourcePath("shaders/PrefilteredEnvMap.sbl")
    );

    _viewLoc = _shaderProgram->getUniformLoc("view");
    _projLoc = _shaderProgram->getUniformLoc("projection");
    _roughnessLoc = _shaderProgram->getUniformLoc("roughness");
}

PrefilteredEnvMapGenerator::~PrefilteredEnvMapGenerator()
{
}

void PrefilteredEnvMapGenerator::renderFace(
    const glm::mat4& viewMatrix,
    const glm::mat4& projectionMatrix
)
{
    float roughness = static_cast<float>(getCurrentMipLevel())
        / (getMaxMipLevel() - 1);

    _shaderProgram->use();
    _shaderProgram->setUniform(_viewLoc, viewMatrix);
    _shaderProgram->setUniform(_projLoc, projectionMatrix);
    _shaderProgram->setUniform(_roughnessLoc, roughness);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _environmentCubemap->getId());

    _cube->render();
}

}

#include "fw/rendering/preprocessing/DiffuseIrradianceCubemapGenerator.hpp"
#include "fw/Resources.hpp"

namespace fw
{

DiffuseIrradianceCubemapGenerator::DiffuseIrradianceCubemapGenerator(
    std::shared_ptr<Cubemap> environmentCubemap
):
    _environmentCubemap{environmentCubemap}
{
    _shaderProgram = std::make_shared<ShaderProgram>(
        getFrameworkResourcePath("shaders/DiffuseIrradianceCubemap.sbl")
    );

    _viewLoc = _shaderProgram->getUniformLoc("view");
    _projLoc = _shaderProgram->getUniformLoc("projection");
}

DiffuseIrradianceCubemapGenerator::~DiffuseIrradianceCubemapGenerator()
{
}

void DiffuseIrradianceCubemapGenerator::renderFace(
    const glm::mat4& viewMatrix,
    const glm::mat4& projectionMatrix
)
{
    _shaderProgram->use();
    _shaderProgram->setUniform(_viewLoc, viewMatrix);
    _shaderProgram->setUniform(_projLoc, projectionMatrix);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _environmentCubemap->getId());
    _cube->render();
}

}

#include "fw/rendering/preprocessing/EquirectangularToCubemapConverter.hpp"
#include "fw/Resources.hpp"

namespace fw
{

EquirectangularToCubemapConverter::EquirectangularToCubemapConverter(
    std::shared_ptr<Texture> equirectangularTexture
):
    _equirectangularTexture{equirectangularTexture}
{
    _shaderProgram = std::make_shared<ShaderProgram>(
        getFrameworkResourcePath("shaders/EquirectangularToCubemap.sbl")
    );

    _viewLoc = _shaderProgram->getUniformLoc("view");
    _projLoc = _shaderProgram->getUniformLoc("projection");
}

EquirectangularToCubemapConverter::~EquirectangularToCubemapConverter()
{
}

void EquirectangularToCubemapConverter::renderFace(
    const glm::mat4& viewMatrix,
    const glm::mat4& projectionMatrix
)
{
    _shaderProgram->use();
    _shaderProgram->setUniform(_viewLoc, viewMatrix);
    _shaderProgram->setUniform(_projLoc, projectionMatrix);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _equirectangularTexture->getTextureId());
    _cube->render();
}

}

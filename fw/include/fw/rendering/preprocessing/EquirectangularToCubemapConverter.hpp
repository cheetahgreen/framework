#pragma once
#include <memory>
#include "fw/Texture.hpp"
#include "CubemapGeneratorBase.hpp"

namespace fw
{

class EquirectangularToCubemapConverter:
    public CubemapGeneratorBase
{
public:
    EquirectangularToCubemapConverter(
        std::shared_ptr<Texture> equirectangularTexture
    );

    virtual ~EquirectangularToCubemapConverter();

protected:
    virtual void renderFace(
        const glm::mat4& viewMatrix,
        const glm::mat4& projectionMatrix
    ) override;

private:
    std::shared_ptr<ShaderProgram> _shaderProgram;
    GLint _viewLoc, _projLoc;
    std::shared_ptr<Texture> _equirectangularTexture;
};

}

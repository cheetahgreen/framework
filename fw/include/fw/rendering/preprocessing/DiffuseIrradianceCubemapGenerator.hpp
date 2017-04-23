#pragma once
#include <memory>
#include "fw/resources/Cubemap.hpp"
#include "CubemapGeneratorBase.hpp"

namespace fw
{

class DiffuseIrradianceCubemapGenerator:
    public CubemapGeneratorBase
{
public:
    DiffuseIrradianceCubemapGenerator(
        std::shared_ptr<Cubemap> environmentCubemap
    );

    virtual ~DiffuseIrradianceCubemapGenerator();

protected:
    virtual void renderFace(
        const glm::mat4& viewMatrix,
        const glm::mat4& projectionMatrix
    ) override;

private:
    std::shared_ptr<ShaderProgram> _shaderProgram;
    GLint _viewLoc, _projLoc;
    std::shared_ptr<Cubemap> _environmentCubemap;
};

}

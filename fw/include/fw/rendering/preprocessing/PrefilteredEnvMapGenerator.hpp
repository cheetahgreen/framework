#pragma once
#include <memory>
#include "fw/resources/Cubemap.hpp"
#include "CubemapGeneratorBase.hpp"

namespace fw
{

class PrefilteredEnvMapGenerator:
    public CubemapGeneratorBase
{
public:
    PrefilteredEnvMapGenerator(
        std::shared_ptr<Cubemap> environmentCubemap
    );

    virtual ~PrefilteredEnvMapGenerator();

protected:
    virtual void renderFace(
        const glm::mat4& viewMatrix,
        const glm::mat4& projectionMatrix
    ) override;

private:
    std::shared_ptr<ShaderProgram> _shaderProgram;
    GLint _viewLoc, _projLoc, _roughnessLoc;
    std::shared_ptr<Cubemap> _environmentCubemap;
};

}

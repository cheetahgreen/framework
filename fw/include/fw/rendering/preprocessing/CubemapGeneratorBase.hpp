#pragma once

#include <array>
#include <memory>
#include "glm/glm.hpp"
#include "fw/Mesh.hpp"
#include "fw/Shaders.hpp"
#include "fw/Vertices.hpp"
#include "fw/resources/Cubemap.hpp"

namespace fw
{

class CubemapGeneratorBase
{
public:
    CubemapGeneratorBase();
    virtual ~CubemapGeneratorBase();

    std::unique_ptr<Cubemap> generate(const glm::ivec2& faceResolution);

protected:
    virtual std::unique_ptr<Cubemap> getEmptyCubemap() const;
    virtual glm::mat4 getProjection() const;
    virtual std::array<glm::mat4, 6> getViews() const;
    virtual void generateBuffers();

    virtual void renderFace(
        const glm::mat4& viewMatrix,
        const glm::mat4& projectionMatrix
    ) = 0;

    std::shared_ptr<Mesh<VertexNormalTexCoords>> _cube;

private:
    glm::ivec2 _faceResolution;
    GLuint _fbo, _rbo;
    std::shared_ptr<ShaderProgram> _shaderProgram;
};

}

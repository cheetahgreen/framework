#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "IParametricSurfaceUV.hpp"
#include "Mesh.hpp"
#include "Vertices.hpp"

namespace fw
{

class ParametricSurfaceMeshBuilder
{
public:
    ParametricSurfaceMeshBuilder();
    ~ParametricSurfaceMeshBuilder();

    void setSamplingResolution(glm::ivec2 samplingResolution);
    glm::ivec2 getSamplingResolution() const;

    std::shared_ptr<Mesh<VertexNormalTexCoords>> build(
        std::shared_ptr<IParametricSurfaceUV> surface,
        glm::dvec2 minimumParameter = glm::dvec2(0.0, 0.0),
        glm::dvec2 maximumParmeter = glm::dvec2(1.0, 1.0)
    ) const;

private:
    glm::ivec2 _samplingResolution;
};

}

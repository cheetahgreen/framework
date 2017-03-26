#pragma once

#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "fw/Mesh.hpp"
#include "fw/GeometryChunk.hpp"
#include "fw/Vertices.hpp"

namespace fw
{

class FrameMarker
{
public:
    FrameMarker();
    ~FrameMarker();

    void setTransform(const glm::mat4& transformation);

    void setAxisX(const glm::vec3& xAxis);
    void setAxisY(const glm::vec3& yAxis);
    void setAxisZ(const glm::vec3& zAxis);

    std::vector<GeometryChunk> getGeometryChunks();

protected:
    std::vector<GeometryChunk> getGeoChunksOfArrow(
        glm::vec3 from,
        glm::vec3 to,
        glm::vec3 color,
        float thickness
    );

private:
    glm::vec3 _xAxis, _yAxis, _zAxis;
    glm::mat4 _transformation;

    std::shared_ptr<Mesh<VertexNormalTexCoords>> _cone;
    std::shared_ptr<Mesh<VertexNormalTexCoords>> _cylinder;
};

}

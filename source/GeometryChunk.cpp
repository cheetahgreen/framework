#include "fw/GeometryChunk.hpp"

namespace fw
{

GeometryChunk::GeometryChunk(
    const std::shared_ptr<IMesh>& mesh,
    const std::shared_ptr<Material>& material,
    const glm::mat4& modelMatrix
):
    _mesh{mesh},
    _material{material},
    _modelMatrix{modelMatrix}
{
}

GeometryChunk::~GeometryChunk()
{
}

const std::shared_ptr<IMesh>& GeometryChunk::getMesh() const
{
    return _mesh;
}

const std::shared_ptr<Material>& GeometryChunk::getMaterial() const
{
    return _material;
}

const glm::mat4 GeometryChunk::getModelMatrix() const
{
    return _modelMatrix;
}


}

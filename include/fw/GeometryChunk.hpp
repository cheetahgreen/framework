#pragma once

#include <memory>
#include <string>

#include "fw/Material.hpp"
#include "fw/Mesh.hpp"
#include "fw/OpenGLHeaders.hpp"

namespace fw
{

class GeometryChunk
{
public:
    GeometryChunk(
        const std::shared_ptr<IMesh>& mesh,
        const std::shared_ptr<Material>& material,
        const glm::mat4& modelMatrix
    );
    ~GeometryChunk();

    const std::shared_ptr<IMesh>& getMesh() const;
    const std::shared_ptr<Material>& getMaterial() const;
    const glm::mat4 getModelMatrix() const;

private:
    glm::mat4 _modelMatrix;
    std::shared_ptr<IMesh> _mesh;
    std::shared_ptr<Material> _material;
};

}

#pragma once

#include <string>
#include "assimp/scene.h"
#include "fw/Mesh.hpp"
#include "fw/Vertices.hpp"
#include "fw/GeometryChunk.hpp"

namespace fw
{

class StaticModel
{
public:
    StaticModel(std::vector<fw::GeometryChunk> geometryChunks);
    virtual ~StaticModel();

    const std::vector<fw::GeometryChunk>& getGeometryChunks() const;

private:
    std::vector<fw::GeometryChunk> _geometryChunks;
    std::vector<std::shared_ptr<fw::Mesh<fw::VertexNormalTexCoords>>> _meshes;
};

}

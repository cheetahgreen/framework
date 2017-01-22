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
    StaticModel(const std::string& filepath);
    virtual ~StaticModel();

    void render() const;
    const std::vector<fw::GeometryChunk>& getGeometryChunks() const;

protected:
    bool loadFromFile(const std::string& filepath);
    void processSceneNode(const aiNode *node, const aiScene* scene);
    void processSceneMesh(const aiMesh *mesh, const aiScene* scene);
    void destroy();

private:
    std::string _modelFilename;
    std::vector<fw::GeometryChunk> _geometryChunks;
    std::vector<std::shared_ptr<fw::Mesh<fw::VertexNormalTexCoords>>> _meshes;
};

}

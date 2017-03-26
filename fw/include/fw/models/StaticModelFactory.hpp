#pragma once

#include <memory>
#include <string>
#include "assimp/scene.h"
#include "fw/models/StaticModel.hpp"
#include "fw/resources/TextureManager.hpp"

namespace fw
{

class StaticModelFactory
{
public:
    StaticModelFactory(
        const std::shared_ptr<ITextureManager>& textureManager
    );

    std::shared_ptr<StaticModel> load(
        const std::string& filepath
    );

protected:
    void processSceneNode(const aiNode *node, const aiScene* scene);
    void processSceneMesh(const aiMesh *mesh, const aiScene* scene);

private:
    std::string _modelFilename;
    std::shared_ptr<ITextureManager> _textureManager;

    std::vector<fw::GeometryChunk> _geometryChunks;
    std::vector<std::shared_ptr<fw::Mesh<fw::StandardVertex3D>>> _meshes;
};

}

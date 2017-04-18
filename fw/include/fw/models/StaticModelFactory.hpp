#pragma once

#include <memory>
#include <string>
#include <fstream>
#include "assimp/scene.h"
#include "boost/filesystem.hpp"
#include "fw/models/StaticModel.hpp"
#include "fw/resources/TextureManager.hpp"

namespace fw
{

class StaticModelFactory
{
public:
    StaticModelFactory(
        VirtualFilesystem& vfs,
        const std::shared_ptr<ITextureManager>& textureManager
    );

    std::shared_ptr<StaticModel> load(const boost::filesystem::path& filepath);

protected:
    std::shared_ptr<StaticModel> loadScene(const aiScene* scene);
    void processSceneNode(const aiNode *node, const aiScene* scene);
    void processSceneMesh(const aiMesh *mesh, const aiScene* scene);

private:
    VirtualFilesystem& _vfs;
    std::shared_ptr<ITextureManager> _textureManager;

    std::vector<fw::GeometryChunk> _geometryChunks;
    std::vector<std::shared_ptr<fw::Mesh<fw::StandardVertex3D>>> _meshes;
};

}

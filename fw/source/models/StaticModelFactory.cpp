#include "fw/models/StaticModelFactory.hpp"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include "fw/common/Filesystem.hpp"
#include "fw/internal/Logging.hpp"

namespace fw
{

StaticModelFactory::StaticModelFactory(
    VirtualFilesystem& vfs,
    const std::shared_ptr<ITextureManager>& textureManager
):
    _vfs{vfs},
    _textureManager{textureManager}
{
}

std::shared_ptr<StaticModel> StaticModelFactory::load(
    const boost::filesystem::path& filepath
)
{
    _geometryChunks.clear();
    _meshes.clear();

    auto file = _vfs.getFile(filepath);
    auto& stream = file->getStream();

    stream.seekg(0, stream.end);
    auto length = stream.tellg();
    stream.seekg(0, stream.beg);

    std::vector<unsigned char> buffer(length);
    stream.read(reinterpret_cast<char*>(buffer.data()), length);

    auto importFlags = (
        aiProcess_CalcTangentSpace
        | aiProcess_FlipUVs
        | aiProcess_JoinIdenticalVertices
        | aiProcess_SortByPType
        | aiProcess_Triangulate
    );

    Assimp::Importer importer;
    auto scene = importer.ReadFileFromMemory(
        buffer.data(), length, importFlags
    );

    if (!scene
        || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
        || !scene->mRootNode)
    {
        LOG(ERROR) << "Cannot load file: \"" << filepath << "\". Reason: "
            << importer.GetErrorString();
        return nullptr; // todo: error reporting
    }

    return loadScene(scene);
}

std::shared_ptr<StaticModel> StaticModelFactory::loadScene(const aiScene* scene)
{
    processSceneNode(scene->mRootNode, scene);
    return std::make_shared<fw::StaticModel>(_geometryChunks);
}

void StaticModelFactory::processSceneNode(
    const aiNode *node,
    const aiScene* scene
)
{
    for (auto i = 0; i < node->mNumMeshes; ++i)
    {
        const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processSceneMesh(mesh, scene);
    }

    for (auto i = 0; i < node->mNumChildren; ++i)
    {
        processSceneNode(node->mChildren[i], scene);
    }
}

void StaticModelFactory::processSceneMesh(
    const aiMesh *mesh,
    const aiScene* scene
)
{
    std::vector<fw::StandardVertex3D> vertices;
    std::vector<GLuint> indices;

    for (auto i = 0; i < mesh->mNumVertices; ++i)
    {
        fw::StandardVertex3D vertex;

        vertex.position = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        vertex.normal = {
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        };

        vertex.tangent = {
            mesh->mTangents[i].x,
            mesh->mTangents[i].y,
            mesh->mTangents[i].z
        };

        if (mesh->mTextureCoords[0])
        {
            vertex.texCoords = {
                mesh->mTextureCoords[0][i].x,
                1.0f - mesh->mTextureCoords[0][i].y
            };
        }

        vertices.push_back(vertex);
    }

    for (auto i = 0; i < mesh->mNumFaces; ++i)
    {
        const aiFace& face = mesh->mFaces[i];
        for (auto j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    auto material = std::make_shared<fw::Material>();

    /*
    aiMaterial *loadedMaterial = scene->mMaterials[mesh->mMaterialIndex];
    // todo: do something with this limit
    if (loadedMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString str;
        loadedMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);

        std::string finalTexturePath =
            getPathDirectory(_modelFilename) + "/" + str.C_Str();

        std::replace(
            std::begin(finalTexturePath),
            std::end(finalTexturePath),
            '\\',
            '/'
        );

        LOG(INFO) << "Texture requested: " << str.C_Str() << ". Changed to: "
            << finalTexturePath;

        material->AlbedoColor = {1.0f, 1.0f, 1.0f, 1.0f};
        material->AlbedoMap = _textureManager->loadTexture(finalTexturePath);
    }

    if (loadedMaterial->GetTextureCount(aiTextureType_HEIGHT) > 0)
    {
        aiString str;
        loadedMaterial->GetTexture(aiTextureType_HEIGHT, 0, &str);

        std::string finalTexturePath =
            getPathDirectory(_modelFilename) + "/" + str.C_Str();

        std::replace(
            std::begin(finalTexturePath),
            std::end(finalTexturePath),
            '\\',
            '/'
        );

        LOG(INFO) << "Texture requested: " << str.C_Str() << ". Changed to: "
            << finalTexturePath;

        material->NormalMap = _textureManager->loadTexture(finalTexturePath);
    }
    */

    auto gpuMesh = std::make_shared<fw::Mesh<fw::StandardVertex3D>>(
        vertices,
        indices
    );

    _geometryChunks.push_back({gpuMesh, material, {}});
}

}

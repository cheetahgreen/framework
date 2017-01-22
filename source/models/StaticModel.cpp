#include "fw/models/StaticModel.hpp"
#include "fw/common/Filesystem.hpp"
#include "fw/internal/Logging.hpp"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

namespace fw
{

StaticModel::StaticModel(const std::string& filepath)
{
    loadFromFile(filepath);
}

StaticModel::~StaticModel()
{
    destroy();
}

void StaticModel::render() const
{
    for (const auto& mesh: _meshes)
    {
        mesh->render();
    }
}

const std::vector<fw::GeometryChunk>& StaticModel::getGeometryChunks() const
{
    return _geometryChunks;
}

bool StaticModel::loadFromFile(const std::string& filepath)
{
    destroy();

    _modelFilename = filepath;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        filepath,
        (aiProcess_FlipUVs |
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType)
    );

    if (!scene
        || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
        || !scene->mRootNode)
    {
        LOG(ERROR) << "Cannot load file: \"" << filepath << "\". Reason: "
            << importer.GetErrorString();
        return false; // todo: error reporting
    }

    processSceneNode(scene->mRootNode, scene);

    return true;
}

void StaticModel::destroy()
{
}

void StaticModel::processSceneNode(const aiNode *node, const aiScene* scene)
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

void StaticModel::processSceneMesh(const aiMesh *mesh, const aiScene* scene)
{
    std::vector<fw::VertexNormalTexCoords> vertices;
    std::vector<GLuint> indices;

    for (auto i = 0; i < mesh->mNumVertices; ++i)
    {
        fw::VertexNormalTexCoords vertex;
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

        if (mesh->mTextureCoords[0])
        {
            vertex.texCoords = {
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
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
    aiMaterial *loadedMaterial = scene->mMaterials[mesh->mMaterialIndex];
    // todo: do something with this limit
    if (loadedMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString str;
        loadedMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);

        std::string finalTexturePath =
            getPathDirectory(_modelFilename) + "/" + str.C_Str();

        LOG(INFO) << "Texture requested: " << str.C_Str() << ". Changed to: "
            << finalTexturePath;

        material->setAlbedoColor({1.0f, 1.0f, 1.0f, 1.0f});
        material->setAlbedoMap(std::make_shared<fw::Texture>(finalTexturePath));
    }

    auto gpuMesh = std::make_shared<fw::Mesh<fw::VertexNormalTexCoords>>(
        vertices,
        indices
    );

    //_meshes.push_back(gpuMesh);
    _geometryChunks.push_back({gpuMesh, material, {}});
}

}

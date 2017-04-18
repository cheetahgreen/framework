#include "fw/resources/TextureManager.hpp"

namespace fw
{

TextureManager::TextureManager(VirtualFilesystem& vfs):
    _vfs{vfs}
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::setResourcesDirectory(
    const std::string& resourcesDirectory
)
{
    _resourcesDirectory = resourcesDirectory;
}

std::shared_ptr<Texture> TextureManager::loadTexture(
    const boost::filesystem::path& filename
)
{
    auto texturePtr = findTexture(filename.string());

    if (texturePtr == nullptr)
    {
        auto file = _vfs.getFile(filename);
        auto& fileStream = file->getStream();
        texturePtr = std::make_shared<Texture>(fileStream, filename.string());
        _textures.emplace(filename.string(), texturePtr);
    }

    return texturePtr;
}

const std::map<std::string, std::shared_ptr<Texture>>
    TextureManager::getAllTextures() const
{
    return _textures;
}

void TextureManager::collectGarbage()
{
    for (auto it = std::begin(_textures); it != std::end(_textures);)
    {
        if (it->second.use_count() == 1)
        {
            it = _textures.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

std::shared_ptr<Texture> TextureManager::findTexture(
    const std::string& filename
)
{
    auto textureIt = _textures.find(filename);

    if (textureIt == _textures.end())
    {
        return nullptr;
    }

    return textureIt->second;
}

}

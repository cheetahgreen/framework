#include "fw/resources/TextureManager.hpp"

namespace fw
{

TextureManager::TextureManager()
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
    const std::string& filename
)
{
    auto texturePtr = findTexture(filename);

    if (texturePtr == nullptr)
    {
        texturePtr = std::make_shared<Texture>(filename);
        _textures.emplace(filename, texturePtr);
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

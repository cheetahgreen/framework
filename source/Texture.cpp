#include "fw/Texture.hpp"
#include "fw/TextureUtils.hpp"

namespace fw
{

Texture::Texture(GLuint textureId)
{
}

Texture::Texture(const std::string& filepath)
{
    _filepath = filepath;
    _textureId = loadTextureFromFile(filepath);
}

Texture::~Texture()
{
}

const std::string& Texture::getFilePath() const
{
    return _filepath;
}

GLuint Texture::getTextureId() const
{
    return _textureId;
}

}

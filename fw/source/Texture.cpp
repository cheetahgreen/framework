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

glm::ivec2 Texture::getSize(int mipLevel) const
{
    glBindTexture(GL_TEXTURE_2D, _textureId);

    int x, y;

    glGetTexLevelParameteriv(
        GL_TEXTURE_2D,
        mipLevel,
        GL_TEXTURE_WIDTH,
        &x
    );

    glGetTexLevelParameteriv(
        GL_TEXTURE_2D,
        mipLevel,
        GL_TEXTURE_HEIGHT,
        &y
    );

    glBindTexture(GL_TEXTURE_2D, 0);

    return {x,y};
}

}

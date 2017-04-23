#include "fw/resources/Cubemap.hpp"

namespace fw
{

Cubemap::Cubemap():
    _cubemap{}
{
}

Cubemap::Cubemap(
    int faceWidth,
    int faceHeight,
    GLint internalFormat,
    GLenum format
):
    _cubemap{}
{
    glGenTextures(1, &_cubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemap);

    for (auto i = 0; i < 6; ++i)
    {
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0,
            internalFormat,
            faceWidth,
            faceHeight,
            0,
            format,
            GL_FLOAT,
            nullptr
        );
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

Cubemap::Cubemap(const Cubemap& cubemap):
    _cubemap{}
{
}

Cubemap::Cubemap(Cubemap&& cubemap):
    _cubemap{}
{
}

Cubemap::~Cubemap()
{
    if (_cubemap)
    {
        glDeleteTextures(1, &_cubemap);
    }
}

}

#pragma once

#include "fw/OpenGLHeaders.hpp"

namespace fw
{

class Cubemap
{
public:
    Cubemap();
    Cubemap(int faceWidth, int faceHeight, GLint internalFormat, GLenum format);
    Cubemap(const Cubemap& cubemap);
    Cubemap(Cubemap&& cubemap);
    virtual ~Cubemap();

    GLuint getId() const { return _cubemap; }

private:
    GLuint _cubemap;
};

}

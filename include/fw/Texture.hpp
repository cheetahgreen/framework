#pragma once

#include <string>
#include "fw/OpenGLHeaders.hpp"

namespace fw
{

class Texture
{
public:
    Texture(GLuint textureId);
    Texture(const std::string& filepath);
    virtual ~Texture();

    const std::string& getFilePath() const;
    GLuint getTextureId() const;

private:
    std::string _filepath;
    GLuint _textureId;
};

}

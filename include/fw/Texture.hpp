#pragma once

#include <string>
#include "fw/OpenGLHeaders.hpp"
#include "glm/glm.hpp"

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

    glm::ivec2 getSize(int mipLevel = 0) const;

private:
    std::string _filepath;
    GLuint _textureId;
};

}

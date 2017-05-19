#pragma once

#include <memory>
#include "glm/glm.hpp"
#include "fw/Shaders.hpp"
#include "fw/Vertices.hpp"
#include "fw/Texture.hpp"

namespace fw
{

class TextureGeneratorBase
{
public:
    TextureGeneratorBase();
    virtual ~TextureGeneratorBase();

    std::unique_ptr<Texture> generate(
        const glm::ivec2& resolution,
        unsigned int mipLevels = 1
    );

protected:
    virtual void render() = 0;

private:
    virtual std::unique_ptr<Texture> getEmptyTexture();
    virtual void generateBuffers();

    glm::ivec2 _resolution;
    GLuint _fbo, _rbo;
    unsigned int _currentMipLevel, _maxMipLevel;
};

}

#include "fw/rendering/preprocessing/TextureGeneratorBase.hpp"
#include "fw/internal/Logging.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

namespace fw
{

TextureGeneratorBase::TextureGeneratorBase():
    _resolution{},
    _fbo{},
    _rbo{}
{
}

TextureGeneratorBase::~TextureGeneratorBase()
{
}

std::unique_ptr<Texture> TextureGeneratorBase::generate(
    const glm::ivec2& resolution,
    unsigned int mipLevels
)
{
    if (mipLevels <= 0)
    {
        LOG(WARNING) << "Requested no mip levels. Returned to default 1.";
        mipLevels = 1;
    }

    _maxMipLevel = mipLevels;
    _resolution = resolution;

    LOG(DEBUG) << "Texture generation started. Resolution: " << _resolution.x
        << "x" << _resolution.y;

    auto texture = getEmptyTexture();

    generateBuffers();

    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    auto currentResolution = _resolution;

    for (
        _currentMipLevel = 0;
        _currentMipLevel < _maxMipLevel;
        ++_currentMipLevel
    )
    {
        LOG(DEBUG) << "Writing texture = " << texture->getTextureId()
            << " mip level:" << _currentMipLevel << " resolution: "
            << glm::to_string(currentResolution);

        glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
        glRenderbufferStorage(
            GL_RENDERBUFFER,
            GL_DEPTH_COMPONENT24,
            currentResolution.x,
            currentResolution.y
        );

        glViewport(0, 0, currentResolution.x, currentResolution.y);

        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            texture->getTextureId(),
            _currentMipLevel
        );

        glClearColor(1.f, 0.25f, 1.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        render();

        currentResolution /= 2;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    LOG(DEBUG) << "Texture generation done. OpenGL texture id = "
        << texture->getTextureId();

    return texture;
}

std::unique_ptr<Texture> TextureGeneratorBase::getEmptyTexture()
{
    GLuint texture;
    glGenTextures(1, &texture);

    // todo: generalize
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RG16F,
        _resolution.x,
        _resolution.y,
        0,
        GL_RG,
        GL_FLOAT,
        0
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return std::make_unique<Texture>(texture);
}

void TextureGeneratorBase::generateBuffers()
{
    LOG(DEBUG) << "Generating buffers.";

    glGenFramebuffers(1, &_fbo);
    glGenRenderbuffers(1, &_rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);

    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH_COMPONENT24,
        _resolution.x,
        _resolution.y
    );

    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_RENDERBUFFER,
        _rbo
    );
}

}

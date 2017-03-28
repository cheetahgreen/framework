#include "fw/rendering/Framebuffer.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include <stdexcept>
#include "glm/gtx/string_cast.hpp"
#include "fw/internal/Logging.hpp"


namespace fw
{

Framebuffer::Framebuffer(const glm::ivec2& size):
    _size{size},
    _fbo{},
    _colorAttachment{},
    _depthStencilAttachment{}
{
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    createColorAttachment();
    createDepthStencilAttachment();

    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        _colorAttachment,
        0
    );

    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        _depthStencilAttachment,
        0
    );

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG(ERROR) << "Framebuffer is not complete. Requested size: "
            << glm::to_string(_size);
        throw std::logic_error("Framebuffer is not complete.");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::Framebuffer(Framebuffer&& framebuffer)
{
    glDeleteTextures(1, &_depthStencilAttachment);
    glDeleteTextures(1, &_colorAttachment);
    glDeleteFramebuffers(1, &_fbo);
}

Framebuffer::~Framebuffer()
{
}

void Framebuffer::createColorAttachment()
{
    glGenTextures(1, &_colorAttachment);
    glBindTexture(GL_TEXTURE_2D, _colorAttachment);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        _size.x,
        _size.y,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        nullptr
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Framebuffer::createDepthStencilAttachment()
{
    glGenTextures(1, &_depthStencilAttachment);
    glBindTexture(GL_TEXTURE_2D, _depthStencilAttachment);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_DEPTH24_STENCIL8,
        _size.x,
        _size.y,
        0,
        GL_DEPTH_STENCIL,
        GL_UNSIGNED_INT_24_8,
        nullptr
    );

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Framebuffer::use() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}


}

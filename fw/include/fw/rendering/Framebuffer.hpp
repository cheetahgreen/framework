#pragma once

#include "glm/glm.hpp"
#include "fw/OpenGLApplication.hpp"

namespace fw
{

class IFramebuffer
{
public:
    virtual ~IFramebuffer() {}

    virtual glm::ivec2 getSize() const = 0;
    virtual void use() const = 0;
};

class Framebuffer:
    public IFramebuffer
{
public:
    explicit Framebuffer(const glm::ivec2& size);
    Framebuffer(const Framebuffer& framebuffer) = delete;
    Framebuffer(Framebuffer&& framebuffer);
    virtual ~Framebuffer();

    Framebuffer& operator=(const Framebuffer&& other) = delete;

    virtual glm::ivec2 getSize() const override { return _size; }
    virtual void use() const override;

    GLint getColorTexture() const { return _colorAttachment; }
    GLint getDepthStencilTexture() const { return _depthStencilAttachment; }

protected:
    void createColorAttachment();
    void createDepthStencilAttachment();

private:
    glm::ivec2 _size;
    GLuint _fbo;
    GLuint _colorAttachment;
    GLuint _depthStencilAttachment;
};

class DefaultFramebuffer:
    public IFramebuffer
{
public:
    DefaultFramebuffer(const fw::OpenGLApplication& app):
        _application{app}
    {
    }

    virtual ~DefaultFramebuffer() {}

    virtual glm::ivec2 getSize() const override
    {
        return _application.getFramebufferSize();
    }

    virtual void use() const override
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

private:
    const fw::OpenGLApplication& _application;
};

}

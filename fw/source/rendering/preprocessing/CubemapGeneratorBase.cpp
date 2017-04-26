#include "fw/rendering/preprocessing/CubemapGeneratorBase.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "fw/DebugShapes.hpp"

namespace fw
{

CubemapGeneratorBase::CubemapGeneratorBase():
    _faceResolution{},
    _fbo{},
    _rbo{}
{
    _cube = createBox({1.0f, 1.0f, 1.0f});
}

CubemapGeneratorBase::~CubemapGeneratorBase()
{
}

std::unique_ptr<Cubemap> CubemapGeneratorBase::generate(
    const glm::ivec2& faceResolution,
    unsigned int mipLevels
)
{
    if (mipLevels <= 0)
    {
        LOG(WARNING) << "Requested no mip levels. Returned to default 1.";
        mipLevels = 1;
    }

    // if mipLevels is too high make it smaller

    _maxMipLevel = mipLevels;

    LOG(DEBUG) << "Cubemap generation started.";
    _faceResolution = faceResolution;

    auto cubemap = getEmptyCubemap();

    if (mipLevels > 1)
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->getId());

        glTexParameteri(
            GL_TEXTURE_CUBE_MAP,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR
        );

        glTexParameteri(
            GL_TEXTURE_CUBE_MAP,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR
        );

        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    auto captureProjection = getProjection();
    auto captureViews = getViews();

    generateBuffers();

    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    auto currentResolution = _faceResolution;

    for (
        _currentMipLevel = 0;
        _currentMipLevel < _maxMipLevel;
        ++_currentMipLevel
    )
    {
        glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
        glRenderbufferStorage(
            GL_RENDERBUFFER,
            GL_DEPTH_COMPONENT24,
            currentResolution.x,
            currentResolution.y
        );

        glViewport(0, 0, currentResolution.x, currentResolution.y);

        for (auto i = 0; i < 6; ++i)
        {
            glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT0,
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                cubemap->getId(),
                _currentMipLevel
            );

            glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderFace(captureViews[i], captureProjection);
        }

        currentResolution /= 2;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    LOG(DEBUG) << "Cubemap generation done. OpenGL texture id = "
        << cubemap->getId();

    return cubemap;
}

std::unique_ptr<Cubemap> CubemapGeneratorBase::getEmptyCubemap() const
{
    return std::make_unique<Cubemap>(
        _faceResolution.x,
        _faceResolution.y,
        GL_RGB16F,
        GL_RGB
    );
}

glm::mat4 CubemapGeneratorBase::getProjection() const
{
    return glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
}

std::array<glm::mat4, 6> CubemapGeneratorBase::getViews() const
{
    return {{
        glm::lookAt(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3( 1.0f,  0.0f,  0.0f),
            glm::vec3(0.0f, -1.0f,  0.0f)
        ),
        glm::lookAt(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3(0.0f, -1.0f,  0.0f)
        ),
        glm::lookAt(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3( 0.0f,  1.0f,  0.0f),
            glm::vec3(0.0f,  0.0f,  1.0f)
        ),
        glm::lookAt(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3( 0.0f, -1.0f,  0.0f),
            glm::vec3(0.0f,  0.0f, -1.0f)
        ),
        glm::lookAt(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3( 0.0f,  0.0f,  1.0f),
            glm::vec3(0.0f, -1.0f,  0.0f)
        ),
        glm::lookAt(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3( 0.0f,  0.0f, -1.0f),
            glm::vec3(0.0f, -1.0f,  0.0f)
        )
    }};
}

void CubemapGeneratorBase::generateBuffers()
{
    glGenFramebuffers(1, &_fbo);
    glGenRenderbuffers(1, &_rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);

    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH_COMPONENT24,
        _faceResolution.x,
        _faceResolution.y
    );

    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_RENDERBUFFER,
        _rbo
    );
}

}

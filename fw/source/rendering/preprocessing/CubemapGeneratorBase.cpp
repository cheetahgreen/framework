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
    const glm::ivec2& faceResolution
)
{
    _faceResolution = faceResolution;

    auto cubemap = getEmptyCubemap();
    auto captureProjection = getProjection();
    auto captureViews = getViews();

    LOG(INFO) << "Generating cubemap with (id=" << cubemap->getId() << ")";

    generateBuffers();

    glViewport(0, 0, _faceResolution.x, _faceResolution.y);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->getId());

    for (auto i = 0; i < 6; ++i)
    {
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            cubemap->getId(),
            0
        );

        glClearColor(1.0f, 0, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderFace(captureViews[i], captureProjection);
    }

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

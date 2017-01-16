#include "fw/effects/Standard2DEffect.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "fw/Resources.hpp"

namespace fw
{

Standard2DEffect::Standard2DEffect():
    _diffuseMapTintColor{1.0f, 1.0f, 1.0f, 1.0f},
    _emissionColor{1.0f, 1.0f, 1.0f}
{
    createShaders();
    getUniformLocations();
}

Standard2DEffect::~Standard2DEffect()
{
}

void Standard2DEffect::destroy()
{
}

void Standard2DEffect::begin()
{
    _shaderProgram->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseMap);

    _shaderProgram->setUniform(_textureLocation, 0);
    _shaderProgram->setUniform(_modelMatrixLocation, _modelMatrix);
    _shaderProgram->setUniform(_viewMatrixLocation, _viewMatrix);
    _shaderProgram->setUniform(_projMatrixLocation, _projMatrix);
    _shaderProgram->setUniform(
        _diffuseMapTintColorLocation,
        _diffuseMapTintColor
    );
    _shaderProgram->setUniform(_emissionColorLocation, _emissionColor);
}

void Standard2DEffect::end()
{
}

glm::mat4 Standard2DEffect::getModelMatrix()
{
    return _modelMatrix;
}

void Standard2DEffect::setModelMatrix(const glm::mat4 &modelMatrix)
{
    _modelMatrix = modelMatrix;
}

glm::mat4 Standard2DEffect::getViewMatrix()
{
    return _viewMatrix;
}

void Standard2DEffect::setViewMatrix(const glm::mat4 &viewMatrix)
{
    _viewMatrix = viewMatrix;
}

glm::mat4 Standard2DEffect::getProjectionMatrix()
{
    return _projMatrix;
}

void Standard2DEffect::setProjectionMatrix(const glm::mat4 &projMatrix)
{
    _projMatrix = projMatrix;
}

void Standard2DEffect::setDiffuseTextureTintColor(const glm::vec4& color)
{
    _diffuseMapTintColor = color;
}

void Standard2DEffect::setDiffuseTexture(GLuint textureId)
{
    _diffuseMap = textureId;
}

void Standard2DEffect::setEmissionColor(const glm::vec3& emission)
{
    _emissionColor = emission;
}

void Standard2DEffect::createShaders()
{
    std::shared_ptr<Shader> vs = std::make_shared<Shader>();
    vs->addSourceFromFile(
        getFrameworkResourcePath("shaders/Standard2D.vert")
    );
    vs->compile(GL_VERTEX_SHADER);

    std::shared_ptr<Shader> fs = std::make_shared<Shader>();
    fs->addSourceFromFile(
        getFrameworkResourcePath("shaders/Standard2D.frag")
    );
    fs->compile(GL_FRAGMENT_SHADER);

    _shaderProgram = std::make_shared<ShaderProgram>();
    _shaderProgram->attach(vs.get());
    _shaderProgram->attach(fs.get());
    _shaderProgram->link();
}

void Standard2DEffect::getUniformLocations()
{
    _textureLocation = glGetUniformLocation(
        _shaderProgram->getId(),
        "TextureSlot1"
    );

    _modelMatrixLocation = glGetUniformLocation(
        _shaderProgram->getId(),
        "model"
    );

    _viewMatrixLocation = glGetUniformLocation(
        _shaderProgram->getId(),
        "view"
    );

    _projMatrixLocation = glGetUniformLocation(
        _shaderProgram->getId(),
        "proj"
    );

    _diffuseMapTintColorLocation = glGetUniformLocation(
        _shaderProgram->getId(),
        "DiffuseMapTintColor"
    );

    _emissionColorLocation = glGetUniformLocation(
        _shaderProgram->getId(),
        "EmissionColor"
    );
}

}

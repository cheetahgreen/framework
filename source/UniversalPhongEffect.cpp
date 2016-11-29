#include "fw/UniversalPhongEffect.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Config.hpp"

namespace fw
{

UniversalPhongEffect::UniversalPhongEffect():
    _diffuseMapColor{0.0, 0.0, 0.0, 0.0},
    _solidColor{1.0, 0.0, 0.0, 1.0},
    _lightDirection{0.0, 1.0, 0.0},
    _diffuseMap{0}
{
    createShaders();

    _textureLocation = glGetUniformLocation(
        _shaderProgram->getId(),
        "TextureSlot1"
    );

    _lightDirectionLocation = glGetUniformLocation(
        _shaderProgram->getId(),
        "LightDirection"
    );

    _solidColorLocation = glGetUniformLocation(
        _shaderProgram->getId(),
        "SolidColor"
    );

    _diffuseColorLocation = glGetUniformLocation(
        _shaderProgram->getId(),
        "DiffuseMapColor"
    );
}

UniversalPhongEffect::~UniversalPhongEffect()
{
}

void UniversalPhongEffect::destroy()
{
}

void UniversalPhongEffect::begin()
{
    _shaderProgram->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseMap);
    glUniform1i(_textureLocation, 0);

    glUniform3fv(_lightDirectionLocation, 1, glm::value_ptr(_lightDirection));
    glUniform4fv(_solidColorLocation, 1, glm::value_ptr(_solidColor));
    glUniform4fv(_diffuseColorLocation, 1, glm::value_ptr(_diffuseMapColor));
}

void UniversalPhongEffect::end()
{
}

void UniversalPhongEffect::setLightDirection(glm::vec3 lightDirection)
{
    _lightDirection = lightDirection;
}

void UniversalPhongEffect::setDiffuseTextureColor(glm::vec4 diffuseMultipler)
{
    _diffuseMapColor = diffuseMultipler;
}

void UniversalPhongEffect::setDiffuseTexture(GLuint textureId)
{
    _diffuseMap = textureId;
}

void UniversalPhongEffect::setSolidColor(glm::vec3 color)
{
    _solidColor = glm::vec4{color, 1.0};
}

void UniversalPhongEffect::setSolidColor(glm::vec4 color)
{
    _solidColor = color;
}

void UniversalPhongEffect::createShaders()
{
    std::shared_ptr<Shader> vs = std::make_shared<Shader>();
    vs->addSourceFromFile(RESOURCE("shaders/UniversalPhong.vert"));
    vs->compile(GL_VERTEX_SHADER);

    std::shared_ptr<Shader> fs = std::make_shared<Shader>();
    fs->addSourceFromFile(RESOURCE("shaders/UniversalPhong.frag"));
    fs->compile(GL_FRAGMENT_SHADER);

    _shaderProgram = std::make_shared<ShaderProgram>();
    _shaderProgram->attach(vs.get());
    _shaderProgram->attach(fs.get());
    _shaderProgram->link();
}

}

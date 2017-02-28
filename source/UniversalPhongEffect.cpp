#include "fw/UniversalPhongEffect.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "fw/Resources.hpp"

namespace fw
{

UniversalPhongEffect::UniversalPhongEffect():
    _diffuseMapColor{0.0, 0.0, 0.0, 0.0},
    _solidColor{1.0, 0.0, 0.0, 1.0},
    _lightDirection{0.0, 1.0, 0.0},
    _diffuseMap{nullptr}
{
    createShaders();

    _textureLocation = _shaderProgram->getUniformLoc("AlbedoMapSampler");
    _normalMapLoc = _shaderProgram->getUniformLoc("NormalMapSampler");
    _lightDirectionLocation = _shaderProgram->getUniformLoc("LightDirection");
    _emissionColorLocation = _shaderProgram->getUniformLoc("EmissionColor");
    _solidColorLocation = _shaderProgram->getUniformLoc("SolidColor");
    _diffuseColorLocation = _shaderProgram->getUniformLoc("DiffuseMapColor");
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

    if (_diffuseMap != nullptr)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _diffuseMap->getTextureId());
        glUniform1i(_textureLocation, 0);
    }

    if (_normalMap != nullptr)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _normalMap->getTextureId());
        glUniform1i(_normalMapLoc, 1);
    }

    glUniform3fv(_lightDirectionLocation, 1, glm::value_ptr(_lightDirection));
    glUniform3fv(_emissionColorLocation, 1, glm::value_ptr(_emissionColor));
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

void UniversalPhongEffect::setMaterial(const fw::Material& material)
{
    setEmissionColor(material.getEmissionColor());
    setSolidColor(material.getAlbedoColor());
}

void UniversalPhongEffect::setDiffuseTextureColor(glm::vec4 diffuseMultipler)
{
    _diffuseMapColor = diffuseMultipler;
}

void UniversalPhongEffect::setDiffuseTexture(
    const std::shared_ptr<fw::Texture>& texture
)
{
    _diffuseMap = texture;
}

void UniversalPhongEffect::setNormalMap(
    const std::shared_ptr<fw::Texture>& normalMap
)
{
    _normalMap = normalMap;
}

void UniversalPhongEffect::setEmissionColor(glm::vec3 color)
{
    _emissionColor = color;
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
    _shaderProgram = std::make_shared<ShaderProgram>(
        getFrameworkResourcePath("shaders/UniversalPhong.sbl")
    );
}

}

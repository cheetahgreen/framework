#include "fw/UniversalPhongEffect.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "fw/Resources.hpp"

namespace fw
{

UniversalPhongEffect::UniversalPhongEffect():
    _diffuseMap{nullptr},
    _diffuseMapColor{0.0, 0.0, 0.0, 0.0},
    _solidColor{1.0, 0.0, 0.0, 1.0}
{
    createShaders();

    _textureLocation = _shaderProgram->getUniformLoc("AlbedoMapSampler");
    _normalMapLoc = _shaderProgram->getUniformLoc("NormalMapSampler");
    _metalnessMapLoc = _shaderProgram->getUniformLoc("MetalnessMapSampler");
    _roughnessMapLoc = _shaderProgram->getUniformLoc("RoughnessMapSampler");
    _irradianceMapLoc = _shaderProgram->getUniformLoc("IrradianceMap");
    _lightColorLocation = _shaderProgram->getUniformLoc("LightColor");
    _lightDirectionLocation = _shaderProgram->getUniformLoc("LightDirection");
    _lightPositionLocation = _shaderProgram->getUniformLoc("LightPosition");
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

    if (_metalnessMap != nullptr)
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, _metalnessMap->getTextureId());
        glUniform1i(_metalnessMapLoc, 2);
    }

    if (_roughnessMap != nullptr)
    {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, _roughnessMap->getTextureId());
        glUniform1i(_roughnessMapLoc, 3);
    }

    if (_irradianceMap != nullptr)
    {
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _irradianceMap->getId());
        glUniform1i(_irradianceMapLoc, 4);
    }

    glUniform3fv(_emissionColorLocation, 1, glm::value_ptr(_emissionColor));
    glUniform4fv(_solidColorLocation, 1, glm::value_ptr(_solidColor));
    glUniform4fv(_diffuseColorLocation, 1, glm::value_ptr(_diffuseMapColor));
    updateLightUniforms();

    _shaderActive = true;
}

void UniversalPhongEffect::end()
{
    _shaderActive = false;
}

void UniversalPhongEffect::setLight(
    const fw::Transform& transform,
    const fw::Light& light
)
{
    _lightTransform = transform;
    _light = light;

    if (_shaderActive)
    {
        updateLightUniforms();
    }
}

void UniversalPhongEffect::setMaterial(const fw::Material& material)
{
    setEmissionColor(material.EmissionColor);
    setSolidColor(material.AlbedoColor);
    setDiffuseTexture(material.AlbedoMap);
    setNormalMap(material.NormalMap);
    _metalnessMap = material.MetalnessMap;
    _roughnessMap = material.RoughnessMap;
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

void UniversalPhongEffect::setIrradianceMap(
    const std::shared_ptr<fw::Cubemap>& irradianceCubemap
)
{
    _irradianceMap = irradianceCubemap;
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

void UniversalPhongEffect::updateLightUniforms()
{
    _shaderProgram->setUniform(
        _lightColorLocation,
        _light.getColor()
    );

    _shaderProgram->setUniform(
        _lightPositionLocation,
        _lightTransform.getPosition()
    );
}

void UniversalPhongEffect::createShaders()
{
    _shaderProgram = std::make_shared<ShaderProgram>(
        getFrameworkResourcePath("shaders/UniversalPhong.sbl")
    );
}

}

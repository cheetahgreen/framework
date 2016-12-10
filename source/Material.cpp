#include "fw/Material.hpp"

namespace fw
{

Material::Material()
{
}

Material::~Material()
{
}

void Material::setEmissionColor(const glm::vec3& emissionColor)
{
    _emissionColor = emissionColor;
}

const glm::vec3& Material::getEmissionColor() const
{
    return _emissionColor;
}

void Material::setBaseAlbedoColor(const glm::vec4& baseAlbedoColor)
{
    _baseAlbedoColor = baseAlbedoColor;
}

const glm::vec4& Material::getBaseAlbedoColor() const
{
    return _baseAlbedoColor;
}

void Material::setAlbedoMap(const std::shared_ptr<Texture>& albedoMap)
{
    _albedoMap = albedoMap;
}

const std::shared_ptr<Texture>& Material::getAlbedoMap() const
{
    return _albedoMap;
}

void Material::setSpecularMap(const std::shared_ptr<Texture>& specularMap)
{
    _specularMap = specularMap;
}

const std::shared_ptr<Texture>& Material::getSpecularMap() const
{
    return _specularMap;
}

void Material::setNormalMap(const std::shared_ptr<Texture>& normalMap)
{
    _normalMap = normalMap;
}

const std::shared_ptr<Texture>& Material::getNormalMap() const
{
    return _normalMap;
}


}

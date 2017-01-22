#include "fw/Material.hpp"

namespace fw
{

Material::Material()
{
}

Material::~Material()
{
}

bool Material::hasEmissionColor() const
{
    return true;
}

void Material::setEmissionColor(const glm::vec3& emissionColor)
{
    _emissionColor = emissionColor;
}

const glm::vec3& Material::getEmissionColor() const
{
    return _emissionColor;
}

bool Material::hasAlbedoColor() const
{
    return true;
}

void Material::setAlbedoColor(const glm::vec4& albedoColor)
{
    _albedoColor = albedoColor;
}

const glm::vec4& Material::getAlbedoColor() const
{
    return _albedoColor;
}

bool Material::hasAlbedoMap() const
{
    return _albedoMap != nullptr;
}

void Material::setAlbedoMap(const std::shared_ptr<Texture>& albedoMap)
{
    _albedoMap = albedoMap;
}

const std::shared_ptr<Texture>& Material::getAlbedoMap() const
{
    return _albedoMap;
}

bool Material::hasSpecularMap() const
{
    return _specularMap != nullptr;
}

void Material::setSpecularMap(const std::shared_ptr<Texture>& specularMap)
{
    _specularMap = specularMap;
}

const std::shared_ptr<Texture>& Material::getSpecularMap() const
{
    return _specularMap;
}

bool Material::hasNormalMap() const
{
    return _normalMap != nullptr;
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

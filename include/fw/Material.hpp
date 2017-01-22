#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "fw/Texture.hpp"

namespace fw
{

class Material
{
public:
    Material();
    ~Material();

    bool hasEmissionColor() const;
    void setEmissionColor(const glm::vec3& emissionColor);
    const glm::vec3& getEmissionColor() const;

    bool hasAlbedoColor() const;
    void setAlbedoColor(const glm::vec4& albedoColor);
    const glm::vec4& getAlbedoColor() const;

    bool hasAlbedoMap() const;
    void setAlbedoMap(const std::shared_ptr<Texture>& albedoMap);
    const std::shared_ptr<Texture>& getAlbedoMap() const;

    bool hasSpecularMap() const;
    void setSpecularMap(const std::shared_ptr<Texture>& specularMap);
    const std::shared_ptr<Texture>& getSpecularMap() const;

    bool hasNormalMap() const;
    void setNormalMap(const std::shared_ptr<Texture>& normalMap);
    const std::shared_ptr<Texture>& getNormalMap() const;

private:
    glm::vec3 _emissionColor;
    glm::vec4 _albedoColor;
    std::shared_ptr<Texture> _albedoMap;
    std::shared_ptr<Texture> _specularMap;
    std::shared_ptr<Texture> _normalMap;
};

}

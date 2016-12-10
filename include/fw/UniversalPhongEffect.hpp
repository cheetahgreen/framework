#pragma once

#include <memory>
#include "glm/glm.hpp"

#include "fw/Effect.hpp"
#include "fw/Material.hpp"
#include "fw/Texture.hpp"

namespace fw
{

class UniversalPhongEffect:
    public EffectBase
{
public:
    UniversalPhongEffect();
    virtual ~UniversalPhongEffect();

    virtual void destroy() override;
    virtual void begin() override;
    virtual void end() override;

    void setLightDirection(glm::vec3 lightDirection);

    void setMaterial(const fw::Material& material);

    void setDiffuseTextureColor(glm::vec4 diffuseMultipler);
    void setDiffuseTexture(const std::shared_ptr<fw::Texture>& texture);

    void setEmissionColor(glm::vec3 color);
    void setSolidColor(glm::vec3 color);
    void setSolidColor(glm::vec4 color);

private:
    void createShaders();

    GLuint _textureLocation;
    GLuint _lightDirectionLocation;
    GLuint _emissionColorLocation;
    GLuint _solidColorLocation;
    GLuint _diffuseColorLocation;

    std::shared_ptr<fw::Texture> _diffuseMap;
    glm::vec4 _diffuseMapColor;

    glm::vec3 _emissionColor;
    glm::vec4 _solidColor;

    glm::vec3 _lightDirection;

};

}

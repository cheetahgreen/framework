#pragma once

#include <memory>
#include "glm/glm.hpp"

#include "fw/Effect.hpp"
#include "fw/Texture.hpp"
#include "fw/resources/Cubemap.hpp"
#include "fw/components/Transform.hpp"
#include "fw/rendering/Light.hpp"
#include "fw/rendering/Material.hpp"

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

    void setLight(
        const fw::Transform& transform,
        const fw::Light& light
    );

    void setMaterial(const fw::Material& material);

    void setDiffuseTextureColor(glm::vec4 diffuseMultipler);
    void setDiffuseTexture(const std::shared_ptr<fw::Texture>& texture);
    void setNormalMap(const std::shared_ptr<fw::Texture>& normalMap);
    void setIrradianceMap(const std::shared_ptr<fw::Cubemap>& normalMap);

    void setEmissionColor(glm::vec3 color);
    void setSolidColor(glm::vec3 color);
    void setSolidColor(glm::vec4 color);

protected:
    void updateLightUniforms();

private:
    void createShaders();

    GLint _textureLocation;
    GLint _normalMapLoc;
    GLint _metalnessMapLoc;
    GLint _roughnessMapLoc;
    GLint _irradianceMapLoc;

    GLint _lightColorLocation;
    GLint _lightDirectionLocation;
    GLint _lightPositionLocation;
    GLint _emissionColorLocation;
    GLint _solidColorLocation;
    GLint _diffuseColorLocation;

    bool _shaderActive;

    std::shared_ptr<fw::Texture> _diffuseMap;
    std::shared_ptr<fw::Texture> _normalMap;
    std::shared_ptr<fw::Texture> _metalnessMap;
    std::shared_ptr<fw::Texture> _roughnessMap;
    std::shared_ptr<fw::Cubemap> _irradianceMap;

    fw::Transform _lightTransform;
    fw::Light _light;

    glm::vec4 _diffuseMapColor;
    glm::vec4 _normalMapColor;

    glm::vec3 _emissionColor;
    glm::vec4 _solidColor;
};

}

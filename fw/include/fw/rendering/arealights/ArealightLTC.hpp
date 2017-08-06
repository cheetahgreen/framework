#pragma once

#include "fw/Effect.hpp"
#include "fw/rendering/AreaLight.hpp"
#include "fw/Texture.hpp"

namespace fw
{

class ArealightLTC:
    public EffectBase
{
public:
    ArealightLTC();
    virtual ~ArealightLTC();

    void setArealight(const AreaLight& arealight);
    void setArealightTransform(const glm::mat4& arealightTransform);

    virtual void destroy() override;
    virtual void begin() override;
    virtual void end() override;

private:
    void createShaders();
    void loadLookupTextures();

    AreaLight _arealight;
    glm::mat4 _arealightTransform;

    GLuint _ltcMat;
    GLuint _ltcMag;

    GLint _ltcMatLocation;
    GLint _ltcMagLocation;
    GLint _arealightSizeLocation;
    GLint _arealightTransformLocation;
};

}

#include <iostream>
#include "fw/rendering/arealights/ArealightLTC.hpp"
#include "fw/Resources.hpp"
#include "ltc.inc"

namespace fw
{

ArealightLTC::ArealightLTC()
{
    createShaders();
    loadLookupTextures();
}

ArealightLTC::~ArealightLTC()
{
}

void ArealightLTC::setArealight(const fw::AreaLight& arealight)
{
    _arealight = arealight;
}

void ArealightLTC::setArealightTransform(const glm::mat4& arealightTransform)
{
    _arealightTransform = arealightTransform;
}

void ArealightLTC::destroy()
{
}

void ArealightLTC::begin()
{
    _shaderProgram->use();

    _shaderProgram->setUniform(
        _arealightSizeLocation,
        _arealight.size
    );

    _shaderProgram->setUniform(
        _arealightTransformLocation,
        _arealightTransform
    );

    _shaderProgram->setUniform(_ltcMatLocation, 0);
    _shaderProgram->setUniform(_ltcMagLocation, 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _ltcMat);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _ltcMag);
}

void ArealightLTC::end()
{
}

void ArealightLTC::createShaders()
{
    _shaderProgram = std::make_shared<ShaderProgram>(
        getFrameworkResourcePath("shaders/ArealightLTC.sbl")
    );

    _ltcMatLocation = _shaderProgram->getUniformLoc("ltc_mat");
    _ltcMagLocation = _shaderProgram->getUniformLoc("ltc_mag");
    _arealightSizeLocation = _shaderProgram->getUniformLoc("rectSize");
    _arealightTransformLocation = _shaderProgram->getUniformLoc(
        "rectTransform"
    );
}

void ArealightLTC::loadLookupTextures()
{
    glGenTextures(1, &_ltcMat);
    glGenTextures(1, &_ltcMag);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _ltcMat);

    std::vector<float> textureData;
    textureData.resize(4 * ltclookup::size * ltclookup::size);

    for (auto i = 0; i < ltclookup::size; ++i)
    {
        for (auto j = 0; j < ltclookup::size; ++j)
        {
            auto matIdx = ltclookup::size * j + i;
            auto base = 4 * matIdx;
            const auto& mat = ltclookup::tabM[matIdx];

            const auto& a = mat[0][0];
            const auto& b = mat[0][2];
            const auto& c = mat[1][1];
            const auto& d = mat[2][0];

            textureData[base+0] = a;
            textureData[base+1] = -b;
            textureData[base+2] = (a-b*d)/c;
            textureData[base+3] = -d;
        }
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        ltclookup::size,
        ltclookup::size,
        0,
        GL_RGBA,
        GL_FLOAT,
        textureData.data()
    );

    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "ERROR: " << err << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, _ltcMat);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_R,
        ltclookup::size,
        ltclookup::size,
        0,
        GL_R,
        GL_FLOAT,
        ltclookup::tabAmplitude
    );

}

};

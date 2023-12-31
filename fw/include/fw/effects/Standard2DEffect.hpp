#pragma once

#include "fw/Effect.hpp"

namespace fw
{

class Standard2DEffect
{
public:
    Standard2DEffect();
    virtual ~Standard2DEffect();

    virtual void destroy();
    virtual void begin();
    virtual void end();

    virtual glm::mat4 getModelMatrix();
    virtual void setModelMatrix(const glm::mat4 &modelMatrix);

    virtual glm::mat4 getViewMatrix();
    virtual void setViewMatrix(const glm::mat4 &viewMatrix);

    virtual glm::mat4 getProjectionMatrix();
    virtual void setProjectionMatrix(const glm::mat4 &projMatrix);

    void setDiffuseTextureTintColor(const glm::vec4& color);
    void setDiffuseTexture(GLuint textureId);

    void setEmissionColor(const glm::vec3& emission);

private:
    void createShaders();
    void getUniformLocations();

    GLuint _textureLocation;
    GLuint _modelMatrixLocation;
    GLuint _viewMatrixLocation;
    GLuint _projMatrixLocation;
    GLuint _diffuseMapTintColorLocation;
    GLuint _emissionColorLocation;

    GLuint _diffuseMap;
    glm::mat4 _modelMatrix, _viewMatrix, _projMatrix;

    glm::vec4 _diffuseMapTintColor;
    glm::vec3 _emissionColor;

    std::shared_ptr<ShaderProgram> _shaderProgram;
};

}

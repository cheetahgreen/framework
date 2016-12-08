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
    virtual void setModelMatrix(const glm::mat3 &modelMatrix);

    virtual glm::mat4 getViewMatrix();
    virtual void setViewMatrix(const glm::mat3 &viewMatrix);

    virtual glm::mat4 getProjectionMatrix();
    virtual void setProjectionMatrix(const glm::mat4 &projMatrix);

    void setDiffuseTexture(GLuint textureId);

private:
    void createShaders();
    void getUniformLocations();

    GLuint _textureLocation;
    GLuint _modelMatrixLocation;
    GLuint _viewMatrixLocation;
    GLuint _projMatrixLocation;

    GLuint _diffuseMap;
    glm::mat4 _modelMatrix, _viewMatrix, _projMatrix;

    std::shared_ptr<ShaderProgram> _shaderProgram;
};

}

#pragma once

#include <string>
#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace fw
{

class Shader
{
public:
    Shader();
    Shader(const Shader &shader) = default;
    virtual ~Shader();

    inline GLenum getType() { return _shaderType; }
    inline GLuint getId() { return _shaderId; }

    void addSourceFromFile(const std::string &filename);
    void compile(GLenum shaderType);

private:
    std::vector<std::string> _sources;
    GLenum _shaderType;
    GLuint _shaderId;
};

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    void attach(Shader *shader);
    void link();
    void use();

    void setUniform(GLuint location, GLint v0);
    void setUniform(GLuint location, const glm::vec3& uniform);
    void setUniform(GLuint location, const glm::vec4& uniform);
    void setUniform(GLuint location, const glm::mat4& uniform);

    GLuint getId() { return _program; }

private:
    GLuint _program;
};

}

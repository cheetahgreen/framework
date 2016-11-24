#pragma once

#include "glm/glm.hpp"
#include "OpenGLHeaders.hpp"

namespace fw
{

class Grid
{
public:
    Grid(const glm::ivec2& numQuarterCells, const glm::vec2& cellSize);
    ~Grid();

    void render() const;

private:
    GLuint _vao, _vbo;
    int _numLines;
};

}

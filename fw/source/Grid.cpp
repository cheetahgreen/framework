#include "Grid.hpp"

#include <vector>

#include "Vertices.hpp"

namespace fw
{

Grid::Grid(const glm::ivec2& numQuarterCells, const glm::vec2& cellSize)
{
    std::vector<VertexColor> vertices;
    const glm::vec3 gridColor = {0.3f, 0.3f, 0.3f};

    for (auto z = -numQuarterCells.y; z <= numQuarterCells.y; ++z)
    {
        glm::vec3 start{-cellSize.x * numQuarterCells.x, 0.0f, cellSize.y * z};
        vertices.push_back({start, gridColor});
        vertices.push_back({{-start.x, start.y, start.z}, gridColor});
    }

    for (auto x = -numQuarterCells.x; x <= numQuarterCells.x; ++x)
    {
        glm::vec3 start{cellSize.x * x, 0.0f, -cellSize.y * numQuarterCells.y};
        vertices.push_back({start, gridColor});
        vertices.push_back({{start.x, start.y, -start.z}, gridColor});
    }

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(VertexColor),
        vertices.data(),
        GL_STATIC_DRAW
    );

    VertexColor::setupAttribPointers();

    glBindVertexArray(0);

    _numLines = vertices.size() / 2;
}

Grid::~Grid()
{
    if (_vbo) glDeleteBuffers(1, &_vbo);
    if (_vao) glDeleteVertexArrays(1, &_vao);
    _vao = _vbo = 0;
}

void Grid::render() const
{
    glBindVertexArray(_vao);
    glDrawArrays(GL_LINES, 0, 2 * _numLines);
    glBindVertexArray(0);
}

}

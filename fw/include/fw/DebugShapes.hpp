#pragma once

#include "Mesh.hpp"
#include "Vertices.hpp"

#include <glad/glad.h>

#include <memory>
#include <vector>

namespace fw
{

std::shared_ptr<Mesh<StandardVertex2D>> createQuad2D(glm::vec2 size);

std::unique_ptr<Mesh<VertexNormalTexCoords>> createPlane(
    float width,
    float length
);

std::vector<GLfloat> createCube(float width, float height, float length);

std::shared_ptr<Mesh<VertexNormalTexCoords>> createBox(
    const glm::vec3 &size,
    bool flipNormals = false
);

std::shared_ptr<Mesh<VertexColor>> createBoxOutline(
    const glm::vec3& size,
    const glm::vec3& color = glm::vec3{1.0f, 1.0f, 1.0f}
);

Mesh<VertexNormalTexCoords> createCylinder(
    float height, float radius, float circleSubdivisions
);

Mesh<VertexNormalTexCoords> createSphere(
    float radius,
    int latitudeSubdivisions,
    int longtitudeSubdivisions
);

std::shared_ptr<Mesh<VertexNormalTexCoords>> createCone(
    float height,
    float radius,
    int circleSubdivisions = 16,
    int circleCuts = 16
);

}

#pragma once

#include "Mesh.hpp"
#include "Vertices.hpp"

#include <glad/glad.h>

#include <memory>
#include <vector>

namespace fw
{

Mesh<VertexNormalTexCoords> createPlane(float width, float length);
std::vector<GLfloat> createCube(float width, float height, float length);

std::shared_ptr<Mesh<VertexNormalTexCoords>> createBox(const glm::vec3 &size);

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

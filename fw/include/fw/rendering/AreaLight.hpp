#pragma once

#include "glm/glm.hpp"

namespace fw
{

struct AreaLight
{
public:
    AreaLight():
        size{1.0f, 1.0f},
        color{1.0f, 1.0f, 1.0f},
        isTwoSided{false}
    {
    }

    AreaLight(glm::vec2 size, glm::vec3 color, bool isTwoSided):
        size{size},
        color{color},
        isTwoSided{isTwoSided}
    {
    }

    glm::vec2 size;
    glm::vec3 color;
    bool isTwoSided;
};

}

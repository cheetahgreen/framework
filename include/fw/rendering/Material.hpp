#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "fw/Texture.hpp"

namespace fw
{

struct Material
{
public:
    Material():
        EmissionColor{},
        AlbedoColor{1.0f, 1.0f, 1.0f, 1.0f}
    {
    }

    ~Material()
    {
    }

    glm::vec3 EmissionColor;
    glm::vec4 AlbedoColor;

    std::shared_ptr<Texture> AlbedoMap;
    std::shared_ptr<Texture> NormalMap;
    std::shared_ptr<Texture> MetalnessMap;
    std::shared_ptr<Texture> RoughnessMap;
};

}

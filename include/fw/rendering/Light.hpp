#pragma once

#include "glm/glm.hpp"

namespace fw
{

enum class LightType
{
    Point,
    Directional,
    Spotlight,
    Area
};

class Light
{
public:
    Light() {}
    Light(LightType type, const glm::vec3& color, float range):
        _type{type}, _color{color}, _range{range} {}

    ~Light() {}

    LightType getType() const { return _type; }
    void setType(LightType type) { _type = type; }

    const glm::vec3& getColor() const { return _color; }
    void setColor(const glm::vec3& color) { _color = color; }

    float getRange() const { return _range; }
    void setRange(float range) { _range = range; }

private:
    LightType _type;
    glm::vec3 _color;
    float _range;
};

}

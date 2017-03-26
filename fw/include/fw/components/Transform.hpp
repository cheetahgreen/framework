#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_access.hpp"

namespace fw
{

class Transform
{
public:
    Transform(): _transformMtx{} {}
    Transform(const glm::mat4& transformMtx): _transformMtx{transformMtx} {}

    const glm::mat4& getTransform() const { return _transformMtx; }

    glm::vec3 getPosition() const
    {
        return glm::vec3{glm::column(_transformMtx, 3)};
    }

    void setTransform(const glm::mat4& transformMtx)
    {
        _transformMtx = transformMtx;
    }

private:
    glm::mat4 _transformMtx;
};

}

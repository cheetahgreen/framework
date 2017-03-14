#pragma once
#include "glm/glm.hpp"

namespace fw
{

class Transform
{
public:
    Transform(): _transformMtx{} {}
    Transform(const glm::mat4& transformMtx): _transformMtx{transformMtx} {}

    const glm::mat4& getTransform() const { return _transformMtx; }

    void setTransform(const glm::mat4& transformMtx)
    {
        _transformMtx = transformMtx;
    }

private:
    glm::mat4 _transformMtx;
};

}

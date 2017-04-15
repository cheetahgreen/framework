#pragma once

#include "StaticModel.hpp"

namespace fw
{

class RenderMesh
{
public:
    RenderMesh();
    RenderMesh(std::shared_ptr<StaticModel> mesh);
    virtual ~RenderMesh();

    const std::shared_ptr<StaticModel> getMesh() const { return _mesh; }
    void setMesh(std::shared_ptr<StaticModel> mesh) { _mesh = mesh; }

private:
    std::shared_ptr<StaticModel> _mesh;
};

}

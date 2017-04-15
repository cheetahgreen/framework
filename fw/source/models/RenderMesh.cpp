#include "fw/models/RenderMesh.hpp"

namespace fw
{

RenderMesh::RenderMesh():
    _mesh{}
{
}

RenderMesh::RenderMesh(std::shared_ptr<StaticModel> mesh):
    _mesh{mesh}
{
}

RenderMesh::~RenderMesh()
{
}

}

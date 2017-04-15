#pragma once

#include "fw/models/RenderMesh.hpp"
#include "fw/models/StaticModelFactory.hpp"

namespace fwui
{

class RenderMeshEditor
{
public:
    RenderMeshEditor(std::shared_ptr<fw::StaticModelFactory> meshEditor):
        _meshEditor{meshEditor}
    {
    }

    ~RenderMeshEditor() {}

    void showEmbeddedFor(fw::RenderMesh& renderMesh);

private:
    std::shared_ptr<fw::StaticModelFactory> _meshEditor;
};

}

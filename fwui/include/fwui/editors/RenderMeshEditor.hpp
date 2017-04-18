#pragma once

#include "fw/models/RenderMesh.hpp"
#include "fw/models/StaticModelFactory.hpp"
#include "fwui/widgets/VirtualFSSearch.hpp"

#include <string>

namespace fwui
{

class RenderMeshEditor
{
public:
    RenderMeshEditor(
        fw::VirtualFilesystem& vfs,
        std::shared_ptr<fw::StaticModelFactory> meshFactory
    ):
        _vfs{vfs},
        _fileSearch{vfs},
        _meshFactory{meshFactory}
    {
        _fileSearch.setExtensions({
            ".blend",
            ".fbx",
            ".obj"
        });
    }

    ~RenderMeshEditor() {}

    void showEmbeddedFor(fw::RenderMesh& renderMesh);

private:
    fw::VirtualFilesystem& _vfs;
    fwui::VirtualFSSearch _fileSearch;
    std::shared_ptr<fw::StaticModelFactory> _meshFactory;
};

}

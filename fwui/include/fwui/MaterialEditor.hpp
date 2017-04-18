#pragma once
#include <memory>
#include <string>
#include "fw/rendering/Material.hpp"
#include "fw/resources/TextureManager.hpp"
#include "fw/resources/VirtualFilesystem.hpp"
#include "fwui/widgets/VirtualFSSearch.hpp"

namespace fw
{

class MaterialEditor
{
public:
    MaterialEditor(
        VirtualFilesystem& vfs,
        std::shared_ptr<ITextureManagerWithInspection> textureManager
    );

    ~MaterialEditor();

    void showEmbeddedFor(fw::Material& light);

protected:
    void showTextureEditor(
        const std::string name,
        std::shared_ptr<fw::Texture>& texture
    );

    VirtualFilesystem& _vfs;
    std::shared_ptr<ITextureManagerWithInspection> _textureManager;

    fwui::VirtualFSSearch _search;
    static const std::string _textureDetailsPopupName;
};

}

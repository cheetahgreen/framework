#pragma once
#include <memory>
#include <string>
#include "fw/rendering/Material.hpp"
#include "fw/resources/TextureManager.hpp"

namespace fw
{

class MaterialEditor
{
public:
    MaterialEditor(
        std::shared_ptr<ITextureManagerWithInspection> textureManager
    );

    ~MaterialEditor();

    void showEmbeddedFor(fw::Material& light);

protected:
    void showTextureEditor(
        const std::string name,
        std::shared_ptr<fw::Texture>& texture
    );

    void showQuickTexturePicker();
    bool showTextureListEntry(
        const std::shared_ptr<Texture>& texture,
        const std::string& filter
    );

    std::shared_ptr<ITextureManagerWithInspection> _textureManager;

    std::string _searchText;
    std::shared_ptr<fw::Texture>* _textureContext;
    static const std::string _textureDetailsPopupName;
};

}

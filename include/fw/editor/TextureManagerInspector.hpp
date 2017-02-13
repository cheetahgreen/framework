#pragma once

#include <memory>
#include "fw/resources/TextureManager.hpp"

namespace fw
{

class TextureManagerInspector
{
public:
    TextureManagerInspector(
        const std::shared_ptr<ITextureManagerWithInspection>& textureManager
    );

    virtual ~TextureManagerInspector();

    void show();
    void show(bool& showInspectorFlag);

private:
    bool _inspectorEnabled;
    std::shared_ptr<ITextureManagerWithInspection> _inspectedManager;
    std::shared_ptr<Texture> _selectedTexture;
};

}

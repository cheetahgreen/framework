#include "fwui/TextureManagerInspector.hpp"

#include <string>
#include <vector>
#include "imgui.h"
#include "easylogging++.h"
#include "fwui/ImGuiExtensions.hpp"

namespace fw
{

TextureManagerInspector::TextureManagerInspector(
    const std::shared_ptr<ITextureManagerWithInspection>& textureManager
):
    _inspectorEnabled{true},
    _inspectedManager{textureManager}
{
}

TextureManagerInspector::~TextureManagerInspector()
{
}

void TextureManagerInspector::show()
{
    if (!_inspectorEnabled) { return; }

    if (!ImGui::Begin("Textures Inspector", &_inspectorEnabled))
    {
        ImGui::End();
        return;
    }

    ImGui::BeginChild("TextureInspectorLeftPane", ImVec2(150, 0), true);

    for (auto &texture: _inspectedManager->getAllTextures())
    {
        auto textureName = texture.second->getFilePath();
        auto directoryEnd = textureName.find_last_of("/\\");
        auto textureFilename = textureName.substr(directoryEnd+1);

        bool isSelected = texture.second == _selectedTexture;

        if (ImGui::Selectable(textureFilename.c_str(), isSelected))
        {
            _selectedTexture = texture.second;
        }
    }

    ImGui::EndChild();
    ImGui::SameLine();

    if (_selectedTexture != nullptr)
    {
        ImGui::BeginGroup();

        auto textureSize = _selectedTexture->getSize();
        auto availableWidth = ImGui::GetContentRegionAvailWidth();
        float scale = std::min(1.0f, availableWidth / textureSize.x);

        ImGui::Image(
            reinterpret_cast<void*>(_selectedTexture->getTextureId()),
            ImVec2(scale*textureSize.x, scale*textureSize.y),
            ImVec2(0.0f, 0.0f),
            ImVec2(1.0f, 1.0f),
            ImColor(255, 255, 255, 255),
            ImColor(255, 255, 255, 255)
        );

        ImGui::Text(
            "Texture disk path: %s",
            _selectedTexture->getFilePath().c_str()
        );

        ImGui::Text("Total references: %ld", _selectedTexture.use_count());
        ImGui::Text("Texture resolution: %dx%d", textureSize.x, textureSize.y);

        ImGui::EndGroup();
    }

    ImGui::End();
}

void TextureManagerInspector::show(bool& showInspectorFlag)
{
    _inspectorEnabled = showInspectorFlag;
    show();
    showInspectorFlag = _inspectorEnabled;
}

}


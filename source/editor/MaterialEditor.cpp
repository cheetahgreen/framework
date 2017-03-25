#include "fw/editor/MaterialEditor.hpp"
#include "imgui.h"
#include "ImGuiExtensions.hpp"
#include "boost/filesystem.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace fs = boost::filesystem;

namespace fw
{

const std::string MaterialEditor::_textureDetailsPopupName{
    "MaterialEditorTexDetailsPopup"
};

MaterialEditor::MaterialEditor(
    std::shared_ptr<ITextureManagerWithInspection> textureManager
):
    _textureManager{textureManager}
{
}

MaterialEditor::~MaterialEditor()
{
}

void MaterialEditor::showEmbeddedFor(Material& material)
{
    ImGui::SliderFloat3(
        "Emission",
        glm::value_ptr(material.EmissionColor),
        0.0f,
        1.0f
    );

    ImGui::SliderFloat4(
        "Albedo",
        glm::value_ptr(material.AlbedoColor),
        0.0f,
        1.0f
    );

    showTextureEditor("Albedo", material.AlbedoMap);
    showTextureEditor("Normal", material.NormalMap);
    showTextureEditor("Metalness", material.MetalnessMap);
    showTextureEditor("Roughness", material.RoughnessMap);
    showQuickTexturePicker();
}

void MaterialEditor::showTextureEditor(
    const std::string name,
    std::shared_ptr<fw::Texture>& texture
)
{
    std::string textureFilenameShort{"none"};
    std::string textureFilenameTooltip{};

    if (texture)
    {
        auto pathStr = texture->getFilePath();
        fs::path path(pathStr);
        textureFilenameShort = path.filename().string();
        textureFilenameTooltip = path.string();
    }

    ImGui::Text("%s: %s", name.c_str(), textureFilenameShort.c_str());

    if (textureFilenameTooltip != "" && ImGui::IsItemHovered())
    {
        ImGui::SetTooltip("%s", textureFilenameTooltip.c_str());
    }

    const std::string buttonName{"...##" + name};
    const std::string popupName{"textureEditorPopup" + name};

    ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 30);
    if (ImGui::Button(buttonName.c_str()))
    {
        _textureContext = &texture;
        ImGui::OpenPopup(_textureDetailsPopupName.c_str());
    }

}

void MaterialEditor::showQuickTexturePicker()
{
    if (ImGui::BeginPopup(_textureDetailsPopupName.c_str()))
    {
        if (ImGui::MenuItem(
            "Unset",
            nullptr,
            nullptr,
            *_textureContext != nullptr
        ))
        {
            *_textureContext = nullptr;
        }

        ImGui::Separator();

        ImGui::InputText({"Search"}, _searchText, 128);

        for (auto& texture: _textureManager->getAllTextures())
        {
            if (showTextureListEntry(texture.second, _searchText))
            {
                *_textureContext = texture.second;
            }
        }

        ImGui::EndPopup();
    }
}

bool MaterialEditor::showTextureListEntry(
    const std::shared_ptr<Texture>& texture,
    const std::string& filter
)
{
    fs::path path{texture->getFilePath()};
    std::string filename = path.filename().string();
    bool containsSearch = filename.find(filter) != std::string::npos;

    if (!containsSearch) { return false; }

    return ImGui::Selectable(filename.c_str());
}

}

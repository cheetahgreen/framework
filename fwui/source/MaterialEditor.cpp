#include "fwui/MaterialEditor.hpp"

#include "boost/filesystem.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

#include "fwui/ImGuiExtensions.hpp"

namespace fs = boost::filesystem;

namespace fw
{

const std::string MaterialEditor::_textureDetailsPopupName{
    "MaterialEditorTexDetailsPopup"
};

MaterialEditor::MaterialEditor(
    VirtualFilesystem &vfs,
    std::shared_ptr<ITextureManagerWithInspection> textureManager
):
    _vfs{vfs},
    _textureManager{textureManager},
    _search{vfs}
{
    _search.setExtensions({".png", ".jpg", ".jpeg", ".tga"});
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
}

void MaterialEditor::showTextureEditor(
    const std::string name,
    std::shared_ptr<fw::Texture>& texture
)
{
    ImGui::PushID(texture.get());

    std::string textureFilenameShort{"none"};
    std::string textureFilenameTooltip{};

    if (ImGui::BeginPopup(_textureDetailsPopupName.c_str()))
    {
        if (_search.show())
        {
            auto newTexture = _textureManager->loadTexture(
                _search.getSearchText()
            );

            if (newTexture != nullptr)
            {
                texture = newTexture;
            }
        }
        ImGui::EndPopup();
    }

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

    ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 30);
    if (ImGui::Button("..."))
    {
        _search.clear();
        ImGui::OpenPopup(_textureDetailsPopupName.c_str());
    }

    ImGui::PopID();
}

}

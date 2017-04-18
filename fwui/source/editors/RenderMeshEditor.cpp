#include "fwui/editors/RenderMeshEditor.hpp"
#include "fwui/ImGuiExtensions.hpp"
#include "imgui.h"

namespace fwui
{

void RenderMeshEditor::showEmbeddedFor(fw::RenderMesh& renderMesh)
{
    ImGui::PushID(this);

    auto mesh = renderMesh.getMesh();

    auto chunks = mesh->getGeometryChunks();
    ImGui::Text("Num of chunks: %d", static_cast<int>(chunks.size()));

    if (ImGui::BeginPopup("FileSearchPopup"))
    {
        if (_fileSearch.show())
        {
            auto newMesh = _meshFactory->load(_fileSearch.getSearchText());

            if (newMesh != nullptr)
            {
                renderMesh.setMesh(newMesh);
            }
        }
        ImGui::EndPopup();
    }

    if (_meshFactory != nullptr)
    {
        if (ImGui::Button("Change mesh"))
        {
            ImGui::OpenPopup("FileSearchPopup");
        }
    }

    if (mesh == nullptr)
    {
        ImGui::TextColored({255, 0, 0, 255}, "No mesh loaded.");
    }

    ImGui::PopID();
}

}

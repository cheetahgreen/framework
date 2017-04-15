#include "fwui/editors/RenderMeshEditor.hpp"
#include "imgui.h"

namespace fwui
{

void RenderMeshEditor::showEmbeddedFor(fw::RenderMesh& renderMesh)
{
    auto mesh = renderMesh.getMesh();

    if (mesh == nullptr)
    {
        ImGui::TextColored({255, 0, 0, 255}, "No mesh loaded.");
        return;
    }

    auto chunks = mesh->getGeometryChunks();
    ImGui::Text("Num of chunks: %d", static_cast<int>(chunks.size()));
}

}

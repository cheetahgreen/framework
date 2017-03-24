#include "engine/editor/MaterialEditor.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

namespace ee
{

MaterialEditor::MaterialEditor()
{
}

MaterialEditor::~MaterialEditor()
{
}

void MaterialEditor::showEmbeddedFor(fw::Material& material)
{
    ImGui::SliderFloat(
        "Emission color",
        glm::value_ptr(material.EmissionColor),
        0.0f,
        1.0f
    );

    ImGui::SliderFloat(
        "Albedo color",
        glm::value_ptr(material.EmissionColor),
        0.0f,
        1.0f
    );

    if (material.AlbedoMap)
    {
        ImGui::Text("Albedo map available");
    }

    if (material.NormalMap)
    {
        ImGui::Text("Normal map available");
    }

    if (material.MetalnessMap)
    {
        ImGui::Text("Metalness map available");
    }

    if (material.RoughnessMap)
    {
        ImGui::Text("Roughness map available");
    }
}

}

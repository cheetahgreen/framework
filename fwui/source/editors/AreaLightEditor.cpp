#include "fwui/editors/AreaLightEditor.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

namespace fwui
{

void AreaLightEditor::showEmbeddedFor(fw::AreaLight& areaLight)
{
    ImGui::PushID(this);

    ImGui::DragFloat2(
        "Size",
        glm::value_ptr(areaLight.size),
        0.01f,
        0.0f,
        100.0f
    );

    ImGui::DragFloat3(
        "Color",
        glm::value_ptr(areaLight.color),
        0.01f,
        0.0f,
        100.0f
    );

    ImGui::Checkbox("Is two sided?", &areaLight.isTwoSided);
    ImGui::PopID();
}

}

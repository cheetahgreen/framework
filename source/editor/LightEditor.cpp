#include "fw/editor/LightEditor.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "fw/ImGuiExtensions.hpp"

namespace fw
{

const std::vector<std::string> LightEditor::_defaultLightEnumStrings =
{
    "Point",
    "Directional",
    "Spotlight",
    "Area"
};

LightEditor::LightEditor()
{
}

LightEditor::~LightEditor()
{
}

void LightEditor::showEmbeddedFor(Light& light)
{
    auto typeId = static_cast<int>(light.getType());
    // todo: fix it, highly suboptimal
    std::vector<std::string> typeNames = _defaultLightEnumStrings;
    if (ImGui::Combo("Type", &typeId, typeNames))
    {
        auto newType = static_cast<LightType>(typeId);
        light.setType(newType);
    }

    auto lightType = light.getType();

    auto color = light.getColor();
    ImGui::DragFloat3("Color", glm::value_ptr(color), 0.01f, 0.0f, 100.0f);
    light.setColor(color);

    if (lightType != LightType::Directional)
    {
        auto range = light.getRange();
        ImGui::DragFloat("Range", &range, 0.1f, 0.05f);
        light.setRange(range);
    }
}

}

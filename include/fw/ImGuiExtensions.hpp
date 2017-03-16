#pragma once

#include <string>
#include <vector>
#include "imgui.h"

namespace ImGui
{
    bool InputText(
        const std::string& label,
        std::string& value,
        ImGuiInputTextFlags flags = 0
    );

    bool Combo(
        const char* label,
        int* currIndex,
        std::vector<std::string> &values);

    bool ListBox(
        const char* label,
        int* currIndex,
        std::vector<std::string> &values
    );
}

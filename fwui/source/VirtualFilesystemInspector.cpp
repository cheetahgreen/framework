#include "fwui/VirtualFilesystemInspector.hpp"
#include "imgui.h"
#include "fwui/ImGuiExtensions.hpp"

namespace fwui
{

VirtualFilesystemInspector::VirtualFilesystemInspector(
    fw::VirtualFilesystem& vfs
):
    _inspectorEnabled{false},
    _vfs{vfs}
{
}

VirtualFilesystemInspector::~VirtualFilesystemInspector()
{
}

void VirtualFilesystemInspector::show()
{
    if (!_inspectorEnabled) { return; }

    if (!ImGui::Begin("Content inspector", &_inspectorEnabled))
    {
        ImGui::End();
    }

    ImGui::InputText("Search", _searchString, 255);
    ImGui::Separator();

    auto& rootNode = _vfs.getRootNode();
    showNode(rootNode);

    ImGui::End();
}

void VirtualFilesystemInspector::showNode(const fw::VirtualFsNode& node)
{
    auto name = node.getFilepath().filename().string();

    if (node.isFile() && ImGui::Selectable(name.c_str(), false))
    {
    }

    if (node.isDirectory() && ImGui::TreeNode(name.c_str()))
    {
        for (auto& child: node.getChildren())
        {
            showNode(child);
        }

        ImGui::TreePop();
    }
}

}

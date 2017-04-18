#include "fwui/widgets/VirtualFSSearch.hpp"
#include "fwui/ImGuiExtensions.hpp"
#include "boost/algorithm/string.hpp"

namespace fwui
{

void VirtualFSSearch::setExtensions(std::vector<std::string> extensions)
{
    _extensions.clear();
    for (auto& ext: extensions)
    {
        _extensions.push_back(boost::to_lower_copy(ext));
    }
}

void VirtualFSSearch::clear()
{
    _searchText = std::string{};
    _focusNextFrame = true;
}

bool VirtualFSSearch::show()
{
    ImGui::PushID(this);

    ImGui::InputText("Search", _searchText, 255);
    if (_focusNextFrame)
    {
        ImGui::SetWindowFocus();
        _focusNextFrame = false;
    }

    _itemSelected = false;
    processNode(_vfs.getRootNode());
    ImGui::PopID();
    return _itemSelected;
}

void VirtualFSSearch::processNode(
    const fw::VirtualFsNode& node,
    boost::filesystem::path currentPath
)
{
    auto fullpath = currentPath / node.getFilepath().filename();
    auto name = node.getFilepath().filename().string();

    auto fileExtension = fullpath.extension().string();
    boost::to_lower(fileExtension);

    bool extAllowed = _extensions.size() == 0;

    for (auto& ext: _extensions)
    {
        if (ext == fileExtension)
        {
            extAllowed = true;
            break;
        }
    }

    if (node.isFile()
        && extAllowed
        && fullpath.string().find(_searchText) != std::string::npos)
    {
        if (ImGui::Selectable(fullpath.c_str(), false))
        {
            _searchText = fullpath.string();
            _itemSelected = true;
        }
    }

    if (node.isDirectory())
    {
        for (auto& child: node.getChildren())
        {
            processNode(child, currentPath / node.getFilepath().filename());
        }
    }
}

}

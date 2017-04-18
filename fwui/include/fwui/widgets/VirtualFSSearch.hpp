#pragma once

#include "fw/resources/VirtualFilesystem.hpp"

#include <string>
#include <vector>

namespace fwui
{

class VirtualFSSearch
{
public:
    VirtualFSSearch(fw::VirtualFilesystem& vfs):
        _vfs{vfs},
        _searchText{},
        _focusNextFrame{true}
    {}

    ~VirtualFSSearch() {}

    void setExtensions(std::vector<std::string> extensions);

    void clear();
    bool show();

    std::string getSearchText() { return _searchText; }

protected:
    void processNode(
        const fw::VirtualFsNode& node,
        boost::filesystem::path currentPath = {}
    );

private:
    fw::VirtualFilesystem& _vfs;
    bool _itemSelected;
    std::string _searchText;
    bool _focusNextFrame;

    std::vector<std::string> _extensions;
};

}

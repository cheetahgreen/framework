#pragma once

#include <string>
#include "fw/resources/VirtualFilesystem.hpp"

namespace fwui
{

class VirtualFilesystemInspector
{
public:
    VirtualFilesystemInspector(fw::VirtualFilesystem& vfs);
    ~VirtualFilesystemInspector();

    bool& getShowFlag() { return _inspectorEnabled; }
    void show();

protected:
    void showNode(const fw::VirtualFsNode& node);

private:
    bool _inspectorEnabled;
    fw::VirtualFilesystem& _vfs;
    std::string _searchString;
};

}

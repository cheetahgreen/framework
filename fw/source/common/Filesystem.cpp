#include "fw/common/Filesystem.hpp"

namespace fw
{

std::string getPathDirectory(const std::string& filepath)
{
    // todo: this function works only for Unix paths
    return filepath.substr(0, filepath.find_last_of('/'));
}

}

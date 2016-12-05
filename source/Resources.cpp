#include "fw/Resources.hpp"
#include "Config.hpp"

namespace fw
{

std::string getFrameworkResourcePath(const std::string& relativePath)
{
    return cFrameworkResourcesPath + relativePath;
};

}

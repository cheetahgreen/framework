#include "Resources.hpp"
#include "Config.hpp"

namespace application
{

std::string getApplicationResourcesPath(const std::string& relativePath)
{
    return cApplicationResourcesPath + relativePath;
};

}

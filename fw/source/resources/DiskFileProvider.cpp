#include "fw/resources/DiskFileProvider.hpp"

namespace fs = boost::filesystem;

namespace fw
{

DiskFileProvider::DiskFileProvider(const fs::path& filePath):
    _filePath{filePath}
{
}

DiskFileProvider::~DiskFileProvider()
{
}

std::shared_ptr<IFile> DiskFileProvider::getFile()
{
    auto file = std::make_shared<DiskFile>(_filePath);
    return std::static_pointer_cast<IFile>(file);
}

}

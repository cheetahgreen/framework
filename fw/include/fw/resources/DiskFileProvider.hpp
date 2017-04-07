#pragma once

#include "IFileProvider.hpp"
#include "boost/filesystem.hpp"

namespace fw
{

class DiskFile: public IFile
{
public:
    DiskFile(const boost::filesystem::path& filePath):
        _stream{filePath.string()}
    {
    }

    virtual ~DiskFile() {}

    virtual std::istream& getStream() override { return _stream; }

private:
    std::ifstream _stream;
};

class DiskFileProvider: public IFileProvider
{
public:
    DiskFileProvider(const boost::filesystem::path& filePath);
    virtual ~DiskFileProvider();

    virtual std::shared_ptr<IFile> getFile() override;

private:
    boost::filesystem::path _filePath;
};

}

#pragma once

#include <fstream>

namespace fw
{

class IFile
{
public:
    IFile() {}
    virtual ~IFile() {}
    virtual std::istream& getStream() = 0;
};

class IFileProvider
{
public:
    IFileProvider() {}
    virtual ~IFileProvider() {}

    virtual std::shared_ptr<IFile> getFile() = 0;
};

}

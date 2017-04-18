#pragma once

#include <map>
#include <memory>
#include <vector>

#include "boost/filesystem.hpp"

#include "fw/Texture.hpp"
#include "fw/resources/VirtualFilesystem.hpp"

namespace fw
{

class ITextureManager
{
public:
    ITextureManager() = default;
    virtual ~ITextureManager() = default;

    virtual std::shared_ptr<Texture> loadTexture(
        const boost::filesystem::path& filename
    ) = 0;
};

class ITextureManagerWithInspection:
    public ITextureManager
{
public:
    ITextureManagerWithInspection() = default;
    virtual ~ITextureManagerWithInspection() = default;

    virtual const std::map<std::string, std::shared_ptr<Texture>>
        getAllTextures() const = 0;
};

class TextureManager:
    public ITextureManagerWithInspection
{
public:
    TextureManager(
        VirtualFilesystem& vfs
    );

    virtual ~TextureManager();

    void setResourcesDirectory(const std::string& resourcesDirectory);

    virtual std::shared_ptr<Texture> loadTexture(
        const boost::filesystem::path& filename
    );

    virtual const std::map<std::string, std::shared_ptr<Texture>>
        getAllTextures() const;

    virtual void collectGarbage();

protected:
    std::shared_ptr<Texture> findTexture(
        const std::string& filename
    );

private:
    std::string _resourcesDirectory;
    VirtualFilesystem& _vfs;
    std::map<std::string, std::shared_ptr<Texture>> _textures;
};

}

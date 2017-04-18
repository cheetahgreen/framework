#include "fw/resources/VirtualFilesystem.hpp"
#include "fw/internal/Logging.hpp"
#include "fw/resources/DiskFileProvider.hpp"

#include <stdexcept>

namespace fs = boost::filesystem;

namespace fw
{

VirtualFsNode::VirtualFsNode(
    const boost::filesystem::path& filename,
    std::shared_ptr<IFileProvider> fileProvider
):
    _filename{filename.filename()},
    _fileProvider{fileProvider}
{
}

VirtualFsNode::~VirtualFsNode()
{
}

VirtualFsNode& VirtualFsNode::addChild(VirtualFsNode node)
{
    _children.push_back(std::move(node));
    return _children.back();
}

VirtualFsNode* VirtualFsNode::findChild(
    const boost::filesystem::path& filename
)
{
    auto result = std::find_if(
        std::begin(_children),
        std::end(_children),
        [&filename](VirtualFsNode& node)
        {
            return node.getFilepath() == filename;
        }
    );

    if (result != std::end(_children))
    {
        return &(*result);
    }

    return nullptr;
}

VirtualFilesystem::VirtualFilesystem():
    _rootNode{"/"}
{
}

VirtualFilesystem::~VirtualFilesystem()
{
}

void VirtualFilesystem::addFile(
    const fs::path& filePath,
    const fs::path& virtualFilePath
)
{
    auto fileProvider = std::make_shared<DiskFileProvider>(filePath);

    auto fixedVirtualPath = virtualFilePath;
    if (!virtualFilePath.has_root_directory())
    {
        fixedVirtualPath = _rootNode.getFilepath() / virtualFilePath;
    }

    VirtualFsNode* currentNode = nullptr;
    for (const auto& pathPart: fixedVirtualPath.parent_path())
    {

        if (currentNode == nullptr)
        {
            if (pathPart == _rootNode.getFilepath())
            {
                currentNode = &_rootNode;
                continue;
            }

            throw std::logic_error(
                "Root path \"/\" should be present at the beginning "
                "of every virtual path."
            );
        }

        auto child = currentNode->findChild(pathPart);
        if (child == nullptr)
        {
            child = &currentNode->addChild({pathPart});
        }

        currentNode = child;
    }

    currentNode->addChild({
        fixedVirtualPath.filename(),
        std::static_pointer_cast<IFileProvider>(fileProvider)
    });
}

void VirtualFilesystem::addDirectory(
    const fs::path& directoryPath,
    const fs::path& virtualPrefix
)
{
    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath))
    {
        LOG(ERROR) << "Directory \"" << directoryPath.string()
            << "\" not found.";
        throw std::logic_error("Directory not found.");
    }

    for (auto& entry: fs::directory_iterator(directoryPath))
    {
        if (fs::is_regular_file(entry))
        {
            auto realFilePath = entry.path();
            auto virtualFilePath = virtualPrefix / entry.path().filename();
            addFile(realFilePath, virtualFilePath);
        }
        else if (fs::is_directory(entry))
        {
            addDirectory(entry, virtualPrefix / entry.path().filename());
        }
        else
        {
            LOG(INFO) << "Ignored \"" << entry.path().string()
                << "\" because it's not regular file nor directory";
        }
    }
}

std::shared_ptr<IFile> VirtualFilesystem::getFile(
    const boost::filesystem::path& virtualPath
)
{
    auto currentNode = &_rootNode;
    for (auto node: virtualPath)
    {
        if (node.filename() == "/")
        {
            continue;
        }

        auto nextNode = currentNode->findChild(node);
        if (nextNode == nullptr)
        {
            // todo: change exception type
            throw std::logic_error("Path not found.");
        }

        currentNode = nextNode;
    }

    return currentNode->getFileProvider()->getFile();
}

}

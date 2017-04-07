#pragma once

#include <map>
#include <stack>
#include "boost/filesystem.hpp"
#include "boost/iterator.hpp"
#include "fw/resources/IFileProvider.hpp"

namespace fw
{

class VirtualFsNode
{
public:
    VirtualFsNode(
        const boost::filesystem::path& filename,
        std::shared_ptr<IFileProvider> fileProvider = nullptr
    );

    ~VirtualFsNode();

    const boost::filesystem::path getFilepath() const
    {
        return _filename.filename();
    }

    std::shared_ptr<IFileProvider> getFileProvider() const
    {
        return _fileProvider;
    }

    bool isDirectory() const { return _fileProvider == nullptr; }
    bool isFile() const { return _fileProvider != nullptr; }

    VirtualFsNode& addChild(VirtualFsNode vfsNode);

    const std::vector<VirtualFsNode>& getChildren() const
    {
        return _children;
    }

    VirtualFsNode* findChild(const boost::filesystem::path& filename);

private:
    boost::filesystem::path _filename;
    std::shared_ptr<IFileProvider> _fileProvider;
    std::vector<VirtualFsNode> _children;
};

/*
template <class Value>
class VirtualFsNodeGeneralIterator:
    public boost::iterator_facade<
        VirtualFsNodeGeneralIterator<Value>,
        Value,
        boost::forward_traversal_tag
    >
{
public:
    VirtualFsNodeGeneralIterator() {}

    explicit VirtualFsNodeGeneralIterator(Value *p)
    {
        _locationStack.push({p, 0});
    }

    template <class OtherValue>
    VirtualFsNodeGeneralIterator(
        VirtualFsNodeGeneralIterator<OtherValue> const& other
    ):
        _locationStack{other._locationStack}
    {}

private:
    friend class boost::iterator_core_access;
    template <class> friend class VirtualFsNodeGeneralIterator;

    template <class OtherValue>
    bool equal(VirtualFsNodeGeneralIterator<OtherValue> const& other) const
    {
        return _locationStack == other._locationStack;
    }

    void increment()
    {
        while (!_locationStack.empty()
            && _locationStack.top().index >=
                _locationStack.top().node->getChildren().size())
        {
            _locationStack.pop();
        }

        if (_locationStack.empty()) { return; }

        auto& topElement = _locationStack.top();
        auto nextNode = topElement.node->getChildren()[topElement.index];
        topElement.index += 1;

        _locationStack.push({nextNode, 0});
    }

    Value& dereference() const
    {
        return *_locationStack.top().node;
    }

    struct IteratorLocation
    {
        Value *node;
        int index;
    };

    std::stack<IteratorLocation> _locationStack;
};

typedef VirtualFsNodeGeneralIterator<VirtualFsNode>
    VirtualFsNodeIterator;

typedef VirtualFsNodeGeneralIterator<VirtualFsNode const>
    VirtualFsNodeConstIterator;
*/

class VirtualFilesystem
{
public:
    VirtualFilesystem();
    ~VirtualFilesystem();

    void addFile(
        const boost::filesystem::path& filePath,
        const boost::filesystem::path& virtualFilePath
    );

    void addDirectory(
        const boost::filesystem::path& directoryPath,
        const boost::filesystem::path& virtualPrefix = {}
    );

    std::shared_ptr<IFile> getFile(
        const boost::filesystem::path& virtualPath
    );

    const VirtualFsNode &getRootNode() { return _rootNode; }

private:
    VirtualFsNode _rootNode;
};

}

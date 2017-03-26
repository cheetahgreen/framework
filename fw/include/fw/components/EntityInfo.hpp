#pragma once
#include <string>

namespace fw
{

class EntityInfo
{
public:
    EntityInfo(): _name{"Unnamed"} {}

    explicit EntityInfo(const std::string& name):
        _name{name}
    {}

    ~EntityInfo() {}

    const std::string getName() const { return _name; }
    void setName(const std::string& name) { _name = name; }

private:
    std::string _name;
};

}

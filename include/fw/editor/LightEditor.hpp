#pragma once
#include <string>
#include <vector>
#include "fw/rendering/Light.hpp"

namespace fw
{

class LightEditor
{
public:
    LightEditor();
    ~LightEditor();

    void showEmbeddedFor(Light& light);

protected:
    static const std::vector<std::string> _defaultLightEnumStrings;
};

}

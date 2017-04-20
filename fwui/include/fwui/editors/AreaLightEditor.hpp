#pragma once

#include "fw/rendering/AreaLight.hpp"

namespace fwui
{

class AreaLightEditor
{
public:
    AreaLightEditor() {}
    ~AreaLightEditor() {}

    void showEmbeddedFor(fw::AreaLight& areaLight);
};

}

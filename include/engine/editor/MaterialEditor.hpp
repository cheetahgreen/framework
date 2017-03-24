#pragma once
#include <string>
#include <vector>
#include "fw/rendering/Material.hpp"

namespace ee
{

class MaterialEditor
{
public:
    MaterialEditor();
    ~MaterialEditor();

    void showEmbeddedFor(fw::Material& light);
};

}

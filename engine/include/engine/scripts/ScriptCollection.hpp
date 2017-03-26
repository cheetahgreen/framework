#pragma once
#include <memory>
#include <vector>
#include "IScript.hpp"

namespace ee
{

struct ScriptCollection
{
    explicit ScriptCollection(std::vector<std::shared_ptr<IScript>> scripts):
        scripts{scripts}
    {}

    std::vector<std::shared_ptr<IScript>> scripts;
};

}

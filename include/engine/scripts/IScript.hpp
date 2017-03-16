#pragma once
#include "entityx/entityx.h"
#include "ScriptExecutionContext.hpp"

namespace ee
{

class IScript
{
public:
    virtual ~IScript() {}

    virtual void update(
        entityx::Entity entity,
        ScriptExecutionContext& context
    ) = 0;
};

}

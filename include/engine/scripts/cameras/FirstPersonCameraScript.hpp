#pragma once
#include "../IScript.hpp"
#include "fw/cameras/FirstPersonCameraController.hpp"

namespace ee
{

class FirstPersonCameraScript:
    public IScript
{
public:
    FirstPersonCameraScript();
    virtual ~FirstPersonCameraScript();

    virtual void update(
        entityx::Entity entity,
        ScriptExecutionContext& context
    );

private:
    fw::FirstPersonCameraController _controller;
};

}

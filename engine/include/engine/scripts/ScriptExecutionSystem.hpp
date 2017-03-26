#pragma once
#include <memory>
#include "entityx/entityx.h"
#include "fw/UniversalPhongEffect.hpp"

#include "fw/inputs/IKeyboardInput.hpp"
#include "fw/inputs/IMouseInput.hpp"

#include "engine/info/WindowProperties.hpp"

namespace ee
{

class ScriptExecutionSystem:
    public entityx::System<ScriptExecutionSystem>
{
public:
    ScriptExecutionSystem(
        std::shared_ptr<ee::IWindowProperties> windowProperties,
        std::shared_ptr<fw::IKeyboardInput> keyboardInput,
        std::shared_ptr<fw::IMouseInput> mouseInput
    );

    ~ScriptExecutionSystem();

    virtual void update(
        entityx::EntityManager& entities,
        entityx::EventManager& events,
        entityx::TimeDelta
    ) override;

private:
    std::shared_ptr<ee::IWindowProperties> _windowProperties;
    std::shared_ptr<fw::IKeyboardInput> _keyboardInput;
    std::shared_ptr<fw::IMouseInput> _mouseInput;
};

}

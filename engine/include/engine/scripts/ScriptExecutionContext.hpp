#pragma once

#include <memory>

#include "fw/inputs/IKeyboardInput.hpp"
#include "fw/inputs/IMouseInput.hpp"

#include "engine/info/WindowProperties.hpp"

namespace ee
{

class ScriptExecutionContext
{
public:
    ScriptExecutionContext(
        std::shared_ptr<ee::IWindowProperties> windowProperties,
        std::shared_ptr<fw::IKeyboardInput> keyboardInput,
        std::shared_ptr<fw::IMouseInput> mouseInput
    ):
        _windowProperties{windowProperties},
        _keyboardInput{keyboardInput},
        _mouseInput{mouseInput}
    {}

    ~ScriptExecutionContext() {}

    const ee::IWindowProperties& getWindowProperties()
    {
        return *_windowProperties;
    }

    fw::IKeyboardInput& getKeyboardInput() { return *_keyboardInput; }
    fw::IMouseInput& getMouseInput() { return *_mouseInput; }

private:
    std::shared_ptr<ee::IWindowProperties> _windowProperties;
    std::shared_ptr<fw::IKeyboardInput> _keyboardInput;
    std::shared_ptr<fw::IMouseInput> _mouseInput;
};

}

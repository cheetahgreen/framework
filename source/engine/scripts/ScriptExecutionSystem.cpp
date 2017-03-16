#include "engine/scripts/ScriptExecutionSystem.hpp"
#include "engine/scripts/ScriptExecutionContext.hpp"
#include "engine/scripts/ScriptCollection.hpp"

namespace ee
{

ScriptExecutionSystem::ScriptExecutionSystem(
    std::shared_ptr<ee::IWindowProperties> windowProperties,
    std::shared_ptr<fw::IKeyboardInput> keyboardInput,
    std::shared_ptr<fw::IMouseInput> mouseInput
):
    _windowProperties{windowProperties},
    _keyboardInput{keyboardInput},
    _mouseInput{mouseInput}
{
}

ScriptExecutionSystem::~ScriptExecutionSystem()
{
}

void ScriptExecutionSystem::update(
    entityx::EntityManager& entities,
    entityx::EventManager& events,
    entityx::TimeDelta
)
{
    ScriptExecutionContext executionContext{
        _windowProperties,
        _keyboardInput,
        _mouseInput
    };

    entities.each<ScriptCollection>(
        [&executionContext](
            entityx::Entity entity,
            ScriptCollection& collection
        )
        {
            for (auto& script: collection.scripts)
            {
                script->update(entity, executionContext);
            }
        }
    );
}

}

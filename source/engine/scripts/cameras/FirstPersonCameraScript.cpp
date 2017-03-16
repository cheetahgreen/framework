#include "engine/scripts/cameras/FirstPersonCameraScript.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "fw/components/Transform.hpp"

#include "OpenGLHeaders.hpp"

#include "engine/common/Exceptions.hpp"

namespace ee
{

FirstPersonCameraScript::FirstPersonCameraScript()
{
}

FirstPersonCameraScript::~FirstPersonCameraScript()
{
}

void FirstPersonCameraScript::update(
    entityx::Entity entity,
    ScriptExecutionContext& context
)
{
    auto transformComponent = entity.component<fw::Transform>();
    if (!transformComponent.valid())
    {
        throw MissingComponentException(
            "Required Transform component is missing"
        );
    }

    auto projCameraComponent = entity.component<fw::ProjectionCamera>();
    if (!projCameraComponent.valid())
    {
        throw MissingComponentException(
            "Required ProjectionCamera component is missing"
        );
    }

    glm::vec3 localMovement{};

    if (context.getKeyboardInput().isKeyDown(GLFW_KEY_W))
    {
        localMovement.z -= 1.0f;
    }

    if (context.getKeyboardInput().isKeyDown(GLFW_KEY_S))
    {
        localMovement.z += 1.0f;
    }

    if (context.getKeyboardInput().isKeyDown(GLFW_KEY_A))
    {
        localMovement.x -= 1.0f;
    }

    if (context.getKeyboardInput().isKeyDown(GLFW_KEY_D))
    {
        localMovement.x += 1.0f;
    }

    _controller.moveLocal(localMovement * 0.01f);

    if (context.getMouseInput().isButtonDown(0))
    {
        auto movement = context.getMouseInput().getMovement() * 0.01;
        _controller.rotate(movement.x, movement.y, 0.0f);
    }

    auto invView = glm::inverse(_controller.getViewMatrix());
    transformComponent->setTransform(invView);

    auto framebufferSize = context.getWindowProperties().getFramebufferSize();
    float aspectRatio =
        static_cast<float>(framebufferSize.x) / framebufferSize.y;
    _controller.getProjectionCamera().setAspectRatio(aspectRatio);

    *projCameraComponent = _controller.getProjectionCamera();
}

}

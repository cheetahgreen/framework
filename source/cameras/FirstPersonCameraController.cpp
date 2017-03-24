#include "fw/cameras/FirstPersonCameraController.hpp"
#include "fw/common/Exceptions.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace fw
{

FirstPersonCameraController::FirstPersonCameraController():
    _position{0.0f, 0.0f, 0.0f},
    _orientation{}
{
}

FirstPersonCameraController::FirstPersonCameraController(
    ProjectionCamera projectionCamera
)
{
}

FirstPersonCameraController::~FirstPersonCameraController()
{
}

ProjectionCamera& FirstPersonCameraController::getProjectionCamera()
{
    return _projectionCamera;
}

const ProjectionCamera& FirstPersonCameraController::getProjectionCamera() const
{
    return _projectionCamera;
}

void FirstPersonCameraController::setProjectionCamera(
    const ProjectionCamera& projectionCamera
)
{
    _projectionCamera = projectionCamera;
}

glm::vec3 FirstPersonCameraController::getPosition() const
{
    return _position;
}

void FirstPersonCameraController::setPosition(const glm::vec3 position)
{
    _position = position;
}

glm::quat FirstPersonCameraController::getOrientation()
{
    return _orientation;
}

void FirstPersonCameraController::setOrientation(const glm::quat& orientation)
{
    _orientation = orientation;
}

glm::mat4 FirstPersonCameraController::getViewMatrix()
{
    auto rotation = glm::mat4_cast(glm::normalize(_orientation));
    auto translation = glm::translate({}, -_position);
    return rotation * translation;
}

void FirstPersonCameraController::moveLocal(glm::vec3 localMovement)
{
    auto orientationInv = glm::inverse(_orientation);

    glm::vec3 forwardDirection = glm::normalize(
        orientationInv * glm::vec4{0.0f, 0.0f, 1.0f, 0.0f}
    );

    glm::vec3 rightDirection = glm::normalize(
        orientationInv * glm::vec3{1.0f, 0.0f, 0.0f}
    );

    glm::vec3 upDirection = glm::normalize(
        orientationInv * glm::vec3{0.0f, 1.0f, 0.0f}
    );

    glm::mat3 toGlobalMat{rightDirection, upDirection, forwardDirection};
    glm::vec3 globalMovement = toGlobalMat * localMovement;

    _position += globalMovement;
}

void FirstPersonCameraController::moveGlobal(glm::vec3 globalMovement)
{
    _position += globalMovement;
}

void FirstPersonCameraController::rotate(float yaw, float pitch, float roll)
{
    glm::quat pitchRotQuat= glm::quat{glm::vec3{pitch, 0.0f, 0.0f}};
    glm::quat yawRotQuat= glm::quat{glm::vec3{0.0f, yaw, 0.0f}};
    _orientation = glm::normalize(pitchRotQuat * _orientation);
    _orientation = glm::normalize(_orientation * yawRotQuat);
}

}

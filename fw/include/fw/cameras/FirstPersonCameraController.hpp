#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "ProjectionCamera.hpp"

namespace fw
{

class FirstPersonCameraController
{
public:
    FirstPersonCameraController();
    explicit FirstPersonCameraController(ProjectionCamera projectionCamera);
    ~FirstPersonCameraController();

    ProjectionCamera& getProjectionCamera();
    const ProjectionCamera& getProjectionCamera() const;
    void setProjectionCamera(const ProjectionCamera& projectionCamera);

    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3 position);

    glm::quat getOrientation();
    void setOrientation(const glm::quat& orientation);

    glm::mat4 getViewMatrix();

    void moveLocal(glm::vec3 localMovement);
    void moveGlobal(glm::vec3 globalMovement);
    void rotate(float yaw, float pitch, float roll);

private:
    ProjectionCamera _projectionCamera;
    glm::vec3 _position;
    glm::quat _orientation;
};

}

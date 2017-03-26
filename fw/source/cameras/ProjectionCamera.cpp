#include "fw/cameras/ProjectionCamera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "fw/Common.hpp"

namespace fw
{

ProjectionCamera::ProjectionCamera():
    _isActive{false},
    _projection{ProjectionCameraType::Perspective},
    _aspectRatio{1.0},
    _fieldOfViewRad{fw::pif()/4.0f},
    _nearClippingPlane{0.2f},
    _farClippingPlane{100.0f}
{
}

ProjectionCamera::~ProjectionCamera()
{
}

glm::mat4 ProjectionCamera::getProjectionMatrix() const
{
    glm::mat4 projection{};

    if (_projection == ProjectionCameraType::Perspective)
    {
        projection = glm::perspective(
            glm::degrees(_fieldOfViewRad),
            _aspectRatio,
            _nearClippingPlane,
            _farClippingPlane
        );
    }
    else if (_projection == ProjectionCameraType::Orthographic)
    {
    }

    return projection;
}

}

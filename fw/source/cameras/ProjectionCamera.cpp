#include "fw/cameras/ProjectionCamera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "fw/Common.hpp"

namespace fw
{

ProjectionCamera::ProjectionCamera():
    _isActive{false},
    _projection{ProjectionCameraType::Perspective},
    _fieldOfViewRad{fw::pif()/4.0f},
    _nearClippingPlane{0.2f},
    _farClippingPlane{100.0f}
{
}

ProjectionCamera::~ProjectionCamera()
{
}

glm::mat4 ProjectionCamera::getProjectionMatrix(float aspectRatio) const
{
    glm::mat4 projection{};

    if (_projection == ProjectionCameraType::Perspective)
    {
        projection = glm::perspective(
            glm::degrees(_fieldOfViewRad),
            aspectRatio,
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

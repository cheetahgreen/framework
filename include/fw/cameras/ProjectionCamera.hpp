#pragma once
#include "glm/glm.hpp"

namespace fw
{

enum class ProjectionCameraType
{
    Perspective,
    Orthographic
};

class ProjectionCamera
{
public:
    ProjectionCamera();
    ~ProjectionCamera();

    glm::mat4 getProjectionMatrix() const;

    bool isActive() const { return _isActive; }
    void setActive(bool isActive) { _isActive = isActive; }

    ProjectionCameraType getProjection() const { return _projection; }
    void setProjection(ProjectionCameraType projection)
    {
        _projection = projection;
    }

    float getAspectRatio() const { return _aspectRatio; }
    void setAspectRatio(float aspectRatio) { _aspectRatio = aspectRatio; }

    float getFieldOfView() const { return _fieldOfViewRad; }
    void setFieldOfView(float fieldOfView) { _fieldOfViewRad = fieldOfView; }

    float getNearClippingPlane() const { return _nearClippingPlane; }
    void setNearClippingPlane(float plane) { _nearClippingPlane = plane; }

    float getFarClippingPlane() const { return _farClippingPlane; }
    void setFarClippingPlane(float plane) { _farClippingPlane = plane; }

private:
    bool _isActive;
    ProjectionCameraType _projection;
    float _aspectRatio;
    float _fieldOfViewRad;
    float _nearClippingPlane;
    float _farClippingPlane;
};

}

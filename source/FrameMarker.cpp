#include "fw/FrameMarker.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include "fw/DebugShapes.hpp"


namespace fw
{

FrameMarker::FrameMarker():
    _xAxis{1.0f, 0.0f, 0.0f},
    _yAxis{0.0f, 1.0f, 0.0f},
    _zAxis{0.0f, 0.0f, 1.0f}
{
    _cone = fw::createCone(1.0, 1.0);
    _cylinder = std::make_shared<Mesh<VertexNormalTexCoords>>(
        fw::createCylinder(1.0, 1.0, 16)
    );
}

FrameMarker::~FrameMarker()
{
}

void FrameMarker::setTransform(const glm::mat4& transformation)
{
    _transformation = transformation;
}

void FrameMarker::setAxisX(const glm::vec3& xAxis)
{
    _xAxis = xAxis;
}

void FrameMarker::setAxisY(const glm::vec3& yAxis)
{
    _yAxis = yAxis;
}

void FrameMarker::setAxisZ(const glm::vec3& zAxis)
{
    _zAxis = zAxis;
}

std::vector<GeometryChunk> FrameMarker::getGeometryChunks()
{
    const float arrowThickness = 0.03f;

    std::vector<GeometryChunk> chunks{};

    auto xAxisChunks = getGeoChunksOfArrow(
        {0, 0, 0},
        _xAxis,
        glm::vec3{1.0f, 0, 0},
        arrowThickness
    );

    auto yAxisChunks = getGeoChunksOfArrow(
        {0, 0, 0},
        _yAxis,
        glm::vec3{0, 1.0f, 0},
        arrowThickness
    );

    auto zAxisChunks = getGeoChunksOfArrow(
        {0, 0, 0},
        _zAxis,
        glm::vec3{0, 0, 1.0f},
        arrowThickness
    );

    std::copy(
        std::begin(xAxisChunks),
        std::end(xAxisChunks),
        std::back_inserter(chunks)
    );

    std::copy(
        std::begin(yAxisChunks),
        std::end(yAxisChunks),
        std::back_inserter(chunks)
    );

    std::copy(
        std::begin(zAxisChunks),
        std::end(zAxisChunks),
        std::back_inserter(chunks)
    );

    return chunks;
}

std::vector<GeometryChunk> FrameMarker::getGeoChunksOfArrow(
    glm::vec3 from,
    glm::vec3 to,
    glm::vec3 color,
    float thickness
)
{
    auto arrowThickness = 1.8f * thickness;
    auto arrowLength = glm::length(to - from);
    auto arrowHeadLength = std::min(2.0f * arrowThickness, arrowLength);

    glm::mat4 coneScale = glm::scale(
        glm::mat4{},
        {arrowThickness, arrowHeadLength, arrowThickness}
    );

    glm::mat4 cylinderScale = glm::scale(
        glm::mat4{},
        {thickness, arrowLength - arrowHeadLength, thickness}
    );

    auto rotationQuat = glm::quat(
        glm::vec3{0, 1.0f, 0.0f},
        glm::normalize(to - from)
    );

    auto rotationMat = glm::mat4_cast(rotationQuat);

    auto coneTranslation = glm::translate(
        glm::mat4{},
        from + (to - from) * ((arrowLength - arrowHeadLength)/(arrowLength))
    );

    auto cylinderTranslation = glm::translate(
        glm::mat4{},
        from + (to - from) * (arrowLength - arrowHeadLength)
            / (2.0f * arrowLength)
    );

    glm::mat4 coneTransformation = coneTranslation * rotationMat * coneScale;
    glm::mat4 cylinderTransformation = cylinderTranslation * rotationMat
        * cylinderScale;

    auto material = std::make_shared<Material>();
    material->setBaseAlbedoColor({color, 1.0f});

    return {
        { _cone, material, coneTransformation},
        {_cylinder, material, cylinderTransformation}
    };

    /*
    _phongEffect->setProjectionMatrix(_projectionMatrix);
    _phongEffect->setViewMatrix(_camera.getViewMatrix());
    _phongEffect->setDiffuseTextureColor({0.0f, 0.0f, 0.0f, 0.0f});
    _phongEffect->setSolidColor(glm::vec4{color, 1.0f});

    _phongEffect->setModelMatrix(coneTransformation);
    _phongEffect->begin();
    _cone->render();
    _phongEffect->end();

    _phongEffect->setModelMatrix(cylinderTransformation);
    _phongEffect->begin();
    _cylinder->render();
    _phongEffect->end();
    */
}

}

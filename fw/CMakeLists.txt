cmake_minimum_required(VERSION 3.0)
project(framework)

set(PROJECT_NAME_TEST ${PROJECT_NAME}-test)
set(DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/dependencies/)

set(FRAMEWORK_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/assets CACHE PATH "")

find_package(OpenGL REQUIRED)

find_package(glfw3 3.3)
if (glfw3_FOUND)
    message("GLFW 3.3 found successfully in ${glfw3_DIR}.")
else()
    message("GLFW 3.3 not found. Library will be compiled from sources.")

    if (WIN32)
        set(GLFW_ADDITIONAL_DEFINITIONS
            "${GLFW_ADDITIONAL_DEFINITIONS} GLFW_EXPOSE_NATIVE_WIN32"
        )

        set(ADDITIONAL_DEFINITIONS
            "${ADDITIONAL_DEFINITIONS} GLFW_EXPOSE_NATIVE_WIN32"
        )
    endif()

    # glfw: do not build docs, tests and examples
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
    add_subdirectory(${DEPENDENCIES_DIR}glfw)
    target_compile_definitions(glfw PRIVATE ${GLFW_ADDITIONAL_DEFINITIONS})
endif()

find_package(assimp)
if (assimp_FOUND)
    message("Assimp found successully in ${assimp_DIR}")
else()
    message("Assimp not found. Library will be compiled from sources.")
    add_subdirectory(${DEPENDENCIES_DIR}assimp)
endif()

find_package(Boost 1.63.0 REQUIRED COMPONENTS filesystem)

enable_testing()
add_subdirectory(${DEPENDENCIES_DIR}googletest)
include_directories(${gtest_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}/include)

add_subdirectory(${DEPENDENCIES_DIR}shabui)

configure_file(
    ${PROJECT_SOURCE_DIR}/configuration/Config.hpp.in
    ${PROJECT_BINARY_DIR}/configuration/Config.hpp
)

set(FRAMEWORK_DEPENDENCIES_SOURCE_FILES
    ${DEPENDENCIES_DIR}/generated/glad/src/glad.c
)

set(FRAMEWORK_SOURCE_FILES
    source/BasicEffect.cpp
    source/Common.cpp
    source/DebugShapes.cpp
    source/Effect.cpp
    source/FrameMarker.cpp
    source/Framework.cpp
    source/FreeCamera.cpp
    source/GeometryChunk.cpp
    source/Grid.cpp
    source/HeightmapGeometry.cpp
    source/HeightmapTextureConverter.cpp
    source/HeightmapVisualizationEffect.cpp
    source/OpenGLApplication.cpp
    source/OrbitingCamera.cpp
    source/PolygonalLine.cpp
    source/Resources.cpp
    source/Shaders.cpp
    source/StbImplementation.c
    source/Texture.cpp
    source/TextureUtils.cpp
    source/TexturedPhongEffect.cpp
    source/UniversalPhongEffect.cpp
    source/Vertices.cpp
    source/cameras/FirstPersonCameraController.cpp
    source/cameras/ProjectionCamera.cpp
    source/common/Filesystem.cpp
    source/effects/Standard2DEffect.cpp
    source/inputs/GenericKeyboardInput.cpp
    source/inputs/GenericMouseInput.cpp
    source/models/RenderMesh.cpp
    source/models/StaticModel.cpp
    source/models/StaticModelFactory.cpp
    source/numerical/BsplineBasisEvaluator.cpp
    source/numerical/BsplineEquidistantKnotGenerator.cpp
    source/numerical/BsplineNonVanishingReparametrization.cpp
    source/numerical/BsplineSurface.cpp
    source/numerical/CommonBsplineSurfaces.cpp
    source/numerical/EquidistantParametricSurface.cpp
    source/numerical/IntersectionCurve.cpp
    source/numerical/ParametricSurfaceClosestPointNaiveFinder.cpp
    source/numerical/ParametricSurfaceIntersection.cpp
    source/numerical/ParametricSurfaceIntersectionFinder.cpp
    source/numerical/ParametricSurfaceMeshBuilder.cpp
    source/numerical/SurfaceIntersectionNewtonIterable.cpp
    source/performance/PerformanceMonitor.cpp
    source/rendering/Framebuffer.cpp
    source/resources/VirtualFilesystem.cpp
    source/resources/DiskFileProvider.cpp
    source/resources/TextureManager.cpp
)

add_library(${PROJECT_NAME}
    ${FRAMEWORK_SOURCE_FILES}
    ${FRAMEWORK_DEPENDENCIES_SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${DEPENDENCIES_DIR}/easyloggingpp/src
    PUBLIC ${DEPENDENCIES_DIR}/generated/glad/include
    PUBLIC ${DEPENDENCIES_DIR}/glfw/include
    PUBLIC ${DEPENDENCIES_DIR}/glm
    PUBLIC ${DEPENDENCIES_DIR}/stb
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_BINARY_DIR}/configuration
    ${PROJECT_SOURCE_DIR}/include/fw
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC ${ADDITIONAL_DEFINITIONS}
)

add_executable(${PROJECT_NAME_TEST}
    test/BsplineBasisEvaluatorTests.cpp
    test/BsplineEquidistantKnotGeneratorTests.cpp
    test/BsplineSurfaceTests.cpp
    test/PointQuadtreeTests.cpp
    test/GeometricIntersectionsTests.cpp
    test/CommonTest.cpp
    test/LinearCombinationEvaluatorTests.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${OPENGL_gl_LIBRARY}
    assimp
    glfw
    shabui
    Boost::boost
    Boost::filesystem
)

target_link_libraries(${PROJECT_NAME_TEST}
    ${PROJECT_NAME}
    gtest
    gmock
    gmock_main
)

set(PROJECT_COMPILE_FEATURES
    ${PROJECT_COMPILE_FEATURES}
    cxx_auto_type
    cxx_nullptr
    cxx_range_for
)

target_compile_features(${PROJECT_NAME}
    PUBLIC ${PROJECT_COMPILE_FEATURES}
)

target_compile_features(${PROJECT_NAME_TEST} PRIVATE
    ${PROJECT_COMPILE_FEATURES}
)

add_test(NAME ${PROJECT_NAME_TEST} COMMAND ${PROJECT_NAME_TEST})

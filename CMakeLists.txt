cmake_minimum_required(VERSION 3.0)
project(framework)

set(PROJECT_NAME_LIB ${PROJECT_NAME}-lib)
set(PROJECT_NAME_TEST ${PROJECT_NAME}-test)
set(DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/dependencies/)

set(FRAMEWORK_BUILD_EXAMPLE ON CACHE BOOL "")
set(FRAMEWORK_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/assets CACHE PATH "")

find_library(OpenGL REQUIRED)

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

enable_testing()
add_subdirectory(${DEPENDENCIES_DIR}googletest)
include_directories(${gtest_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}/include)

set(RESOURCES_PATH ${FRAMEWORK_RESOURCES_DIR})

configure_file(
    ${PROJECT_SOURCE_DIR}/Config.hpp.in
    ${PROJECT_BINARY_DIR}/Config.hpp
)

set(FRAMEWORK_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/include
    ${DEPENDENCIES_DIR}/ImGuizmo
    ${DEPENDENCIES_DIR}/generated/glad/include
    ${DEPENDENCIES_DIR}/glfw/include
    ${DEPENDENCIES_DIR}/glm
    ${DEPENDENCIES_DIR}/imgui
    ${DEPENDENCIES_DIR}/stb
)

set(FRAMEWORK_DEPENDENCIES_SOURCE_FILES
    ${DEPENDENCIES_DIR}/ImGuizmo/ImGuizmo.cpp
    ${DEPENDENCIES_DIR}/generated/glad/src/glad.c
    ${DEPENDENCIES_DIR}/imgui/imgui.cpp
    ${DEPENDENCIES_DIR}/imgui/imgui_demo.cpp
    ${DEPENDENCIES_DIR}/imgui/imgui_draw.cpp
)

set(FRAMEWORK_LIBRARIES
    ${PROJECT_NAME_LIB}
    glfw
    ${OPENGL_gl_LIBRARY}
)

get_directory_property(hasParentScope PARENT_DIRECTORY)
if (hasParentScope)
    set(FRAMEWORK_INCLUDE_DIRS ${FRAMEWORK_INCLUDE_DIRS} PARENT_SCOPE)
    set(FRAMEWORK_DEPENDENCIES_SOURCE_FILES
        ${FRAMEWORK_DEPENDENCIES_SOURCE_FILES}
        PARENT_SCOPE
    )
    set(FRAMEWORK_LIBRARIES ${FRAMEWORK_LIBRARIES} PARENT_SCOPE)
endif()

include_directories(
    ${PROJECT_BINARY_DIR}
    ${FRAMEWORK_INCLUDE_DIRS}
)

set(FRAMEWORK_SOURCE_FILES
    source/BasicEffect.cpp
    source/BsplineBasisEvaluator.cpp
    source/BsplineEquidistantKnotGenerator.cpp
    source/BsplineNonVanishingReparametrization.cpp
    source/BsplineSurface.cpp
    source/Common.cpp
    source/CommonBsplineSurfaces.cpp
    source/DebugShapes.cpp
    source/Effect.cpp
    source/EquidistantParametricSurface.cpp
    source/Grid.cpp
    source/HeightmapGeometry.cpp
    source/HeightmapTextureConverter.cpp
    source/HeightmapVisualizationEffect.cpp
    source/ImGuiApplication.cpp
    source/ImGuiBinding.cpp
    source/IntersectionCurve.cpp
    source/OpenGLApplication.cpp
    source/OrbitingCamera.cpp
    source/ParametricSurfaceClosestPointNaiveFinder.cpp
    source/ParametricSurfaceIntersection.cpp
    source/ParametricSurfaceIntersectionFinder.cpp
    source/ParametricSurfaceMeshBuilder.cpp
    source/PolygonalLine.cpp
    source/Shaders.cpp
    source/StbImplementation.c
    source/SurfaceIntersectionNewtonIterable.cpp
    source/TextureUtils.cpp
    source/TexturedPhongEffect.cpp
    source/Vertices.cpp
)

add_library(${PROJECT_NAME_LIB}
    ${FRAMEWORK_SOURCE_FILES}
    ${FRAMEWORK_DEPENDENCIES_SOURCE_FILES}
)

target_compile_definitions(${PROJECT_NAME_LIB} PRIVATE
    ${ADDITIONAL_DEFINITIONS}
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

target_link_libraries(${PROJECT_NAME_TEST}
    ${PROJECT_NAME_LIB}
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

target_compile_features(${PROJECT_NAME_LIB} PRIVATE ${PROJECT_COMPILE_FEATURES})
target_compile_features(${PROJECT_NAME_TEST} PRIVATE
    ${PROJECT_COMPILE_FEATURES}
)

add_test(NAME ${PROJECT_NAME_TEST} COMMAND ${PROJECT_NAME_TEST})

if (FRAMEWORK_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

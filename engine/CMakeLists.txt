cmake_minimum_required(VERSION 3.0)
project(engine)

set(ENGINE_DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/dependencies/)

add_subdirectory(${ENGINE_DEPENDENCIES_DIR}entityx)

set(ENGINE_SOURCE_FILES
    source/engine/editor/SceneInspector.cpp
    source/engine/rendering/ForwardRenderingSystem.cpp
    source/engine/scripts/ScriptExecutionSystem.cpp
    source/engine/scripts/cameras/FirstPersonCameraScript.cpp
)

add_library(${PROJECT_NAME}
    ${ENGINE_SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC entityx
    PUBLIC framework-ui
)

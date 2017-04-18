cmake_minimum_required(VERSION 3.0)
project(framework-ui)

set(FWUI_DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/dependencies/)

set(FWUI_SOURCE_FILES
    source/ImGuiApplication.cpp
    source/ImGuiBinding.cpp
    source/ImGuiExtensions.cpp
    source/LightEditor.cpp
    source/MaterialEditor.cpp
    source/TextureManagerInspector.cpp
    source/VirtualFilesystemInspector.cpp
    source/editors/RenderMeshEditor.cpp
    source/widgets/VirtualFSSearch.cpp
)

set(FWUI_DEPENDENCIES_SOURCE_FILES
    ${FWUI_DEPENDENCIES_DIR}/ImGuizmo/ImGuizmo.cpp
    ${FWUI_DEPENDENCIES_DIR}/imgui/imgui.cpp
    ${FWUI_DEPENDENCIES_DIR}/imgui/imgui_demo.cpp
    ${FWUI_DEPENDENCIES_DIR}/imgui/imgui_draw.cpp
)

add_library(${PROJECT_NAME}
    ${FWUI_SOURCE_FILES}
    ${FWUI_DEPENDENCIES_SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${FWUI_DEPENDENCIES_DIR}/ImGuizmo
    PUBLIC ${FWUI_DEPENDENCIES_DIR}/imgui
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    framework
)

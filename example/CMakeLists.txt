cmake_minimum_required(VERSION 3.0)
project(framework-example)

set(PROJECT_NAME_LIB ${PROJECT_NAME}-lib)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}
)

add_library(${PROJECT_NAME_LIB}
    source/Application.cpp
)

target_link_libraries(${PROJECT_NAME_LIB}
    PUBLIC framework
)

add_executable(${PROJECT_NAME}
    source/Main.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME_LIB}
)

set(PROJECT_COMPILE_FEATURES
    ${PROJECT_COMPILE_FEATURES}
    cxx_auto_type
    cxx_nullptr
    cxx_range_for
)

target_compile_features(${PROJECT_NAME}
    PRIVATE ${PROJECT_COMPILE_FEATURES}
)

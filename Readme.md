# Framework
Framework is personal graphics framework. It was created to speed up the development of
experimental/university projects.

## Using the framework with git
Fastest way to use the framework is forking **framework-application-template** repository.

If that's not an option then create dependencies directory, add framework source as submodule and sync all sub-dependencies:

```bash
mkdir -p dependencies && mv dependencies
git submodule add git@gitlab.com:sienkiewiczkm/framework.git
git submodule update --init --recursive
cd ..
```

Initialize project using copy of example project, change it's name to more
accurate.

```bash
mv -r dependencies/framework/example/* .
sed -i -- 's/ExampleApplication/AccurateApplicationName/g' ./include/*.hpp ./source/*.cpp
# todo: change namespace
# todo: change filenames
```

Then, edit provided `CMakeLists.txt` for using framework as dependency. Minimalistic file contents:

```cmake
cmake_minimum_required(VERSION 3.0)
project(project-name)

# uncomment if you wish to compile in Debug mode
# set(CMAKE_BUILD_TYPE Debug)

set(PROJECT_NAME_LIB ${PROJECT_NAME}-lib)
set(DEPENDENCIES_DIR dependencies/)

add_subdirectory(${DEPENDENCIES_DIR}/framework)

set(APPLICATION_RESOURCES_PATH ${PROJECT_SOURCE_DIR}/assets/)
configure_file(
    ${PROJECT_SOURCE_DIR}/Config.hpp.in
    ${PROJECT_BINARY_DIR}/Config.hpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}
    ${FRAMEWORK_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME_LIB}
    source/ExampleApplication.cpp
)

add_executable(${PROJECT_NAME}
    source/Main.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME_LIB}
    ${FRAMEWORK_LIBRARIES}
)

set(PROJECT_COMPILE_FEATURES
    ${PROJECT_COMPILE_FEATURES}
    cxx_auto_type
    cxx_nullptr
    cxx_range_for
)

target_compile_features(${PROJECT_NAME} PRIVATE
    ${PROJECT_COMPILE_FEATURES}
)

target_compile_features(${PROJECT_NAME_LIB} PRIVATE
    ${PROJECT_COMPILE_FEATURES}
)
```

## Dependencies
Look into `/dependencies/` subdirectory.

cmake_minimum_required(VERSION 3.0)

set(FRAMEWORK_BUILD_EXAMPLE ON CACHE BOOL "")

add_subdirectory(fw)
add_subdirectory(fwui)
add_subdirectory(engine)

if (FRAMEWORK_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()


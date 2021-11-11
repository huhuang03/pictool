cmake_minimum_required(VERSION 3.12)

# so you still not work??
# still can't find the right x64??
if (NOT DEFINED ENV{VCPKG_ROOT})
    message(FATAL_ERROR Please set the vcpkg_root env)
else()
    if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    endif()
endif()

project(pictool)

add_subdirectory(../QtAwesome/QtAwesome QtAwesome)
add_subdirectory(../easybot easybot)
add_subdirectory(src)
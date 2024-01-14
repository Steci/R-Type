cmake_minimum_required(VERSION 3.20.0)
project(Rtype)

include(FetchContent)

message(STATUS "Fetching VCPKG...")
FetchContent_Declare(
    vcpkg
    URL https://github.com/microsoft/vcpkg/archive/refs/tags/2023.12.12.zip
    URL_MD5 E77B826B0579D653150BDA55643B4143
)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_SOURCE_DIR_CHANGE_WHEN_HASH_MATCH TRUE)
FetchContent_MakeAvailable(vcpkg)


if(WIN32)
    set(CMAKE_GENERATOR "Visual Studio 17 2022" CACHE STRING "CMake generator" FORCE)
    set(VCPKG_TARGET_TRIPLET x64-windows-static-md)
    add_compile_options(-Wall)
else()
    set(CMAKE_GENERATOR "Unix Makefiles" CACHE STRING "CMake generator")
    set(VCPKG_TARGET_TRIPLET x64-linux)
    add_compile_options(-Wall -Wextra -g3)
endif()

message(STATUS "Install VCPKG PACKAGES...")
if(WIN32)
    execute_process(COMMAND "${vcpkg_SOURCE_DIR}/bootstrap-vcpkg.bat")
    execute_process(COMMAND "${vcpkg_SOURCE_DIR}/vcpkg.exe" install --triplet "${VCPKG_TARGET_TRIPLET}")
else()
    execute_process(COMMAND "${vcpkg_SOURCE_DIR}/bootstrap-vcpkg.sh")
    execute_process(COMMAND "${vcpkg_SOURCE_DIR}/vcpkg" install --triplet "${VCPKG_TARGET_TRIPLET}")
endif()

message(STATUS "SETTING UP ENVIRONMENT...")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OpenGL_GL_PREFERENCE GLVND)
set(CMAKE_TOOLCHAIN_FILE "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(VCPKG_INSTALLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed" CACHE STRING "")

message(STATUS "FIND PACKAGES...")
set(CMAKE_PREFIX_PATH "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}")

if (WIN32)
    find_package(raylib CONFIG REQUIRED)
else()
    include(raylib.cmake)
endif()

message(STATUS "START PROJECTS SETUP...")
add_subdirectory(engine)
add_subdirectory(server)
add_subdirectory(client)

cmake_minimum_required(VERSION 3.10)
project(r-type)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT} CACHE STRING "Vcpkg toolchain file")

set(CMAKE_GENERATOR "Unix Makefiles" CACHE STRING "CMake generator")

# add_subdirectory(engine)
add_subdirectory(server)
add_subdirectory(client)
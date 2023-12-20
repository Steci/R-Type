cmake_minimum_required(VERSION 3.10)
project(r-type)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT} CACHE STRING "Vcpkg toolchain file")

set(CMAKE_GENERATOR "Unix Makefiles" CACHE STRING "CMake generator")

project(HelloWorld)

find_package(fmt CONFIG REQUIRED)

add_executable(HelloWorld ../helloworld.cpp)

target_link_libraries(HelloWorld PRIVATE fmt::fmt)

add_custom_command(TARGET HelloWorld POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:HelloWorld> ${CMAKE_SOURCE_DIR}
)

# add_subdirectory(engine)
add_subdirectory(server)
add_subdirectory(client)
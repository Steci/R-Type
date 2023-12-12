<<<<<<< HEAD
cmake_minimum_required(VERSION 3.28)
project(server)
=======
cmake_minimum_required(VERSION 3.10)
project(server_build)
>>>>>>> beb66ab07187e215d7ba6a307930fd87c5a5b13c


if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -Wextra -g3)
endif(CMAKE_COMPILER_IS_GNUCXX)

if (WIN32)
    add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
    #set_target_properties (indie_studio.exe PROPERTIES PREFIX "./build/")
endif(WIN32)

# ADD_LIBRARY(MyStaticLib STATIC)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT} CACHE STRING "Vcpkg toolchain file")

set(CMAKE_GENERATOR "Unix Makefiles" CACHE STRING "CMake generator")

# find_package(sys REQUIRED)

# find_package(netinet REQUIRED)

file(GLOB SOURCES "main.cpp" "src/*.cpp")
add_executable(server_build ${SOURCES})

list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/include")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(server_build PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(server_build pthread)

add_custom_command(TARGET server_build POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:server_build> ${CMAKE_SOURCE_DIR}
)
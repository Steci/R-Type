cmake_minimum_required(VERSION 3.10)
project(client_build)

if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -Wextra -g3)
endif(CMAKE_COMPILER_IS_GNUCXX)

if (WIN32)
    add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
    #set_target_properties (indie_studio.exe PROPERTIES PREFIX "./build/")
endif(WIN32)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT} CACHE STRING "Vcpkg toolchain file")
set(CMAKE_GENERATOR "Unix Makefiles" CACHE STRING "CMake generator")

file(GLOB SOURCES "main.cpp" "src/*.cpp" "src/network/*.cpp")  # Mettez à jour cette ligne

add_executable(client_build ${SOURCES})

list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/include")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(client_build PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(client_build pthread)

add_custom_command(TARGET client_build POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:client_build> ${CMAKE_SOURCE_DIR}
)

cmake_minimum_required(VERSION 3.10)
project(engine)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 20)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(OpenGL_GL_PREFERENCE GLVND)

include(../cmake/Findraylib.cmake)

file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")

add_library(EngineLib STATIC ${ENGINE_SOURCES})

if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -Wextra -g3)
endif(CMAKE_COMPILER_IS_GNUCXX)

if (WIN32)
    add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
endif(WIN32)

add_executable(${PROJECT_NAME} src/main.cpp)

include_directories(includes)

target_link_libraries(${PROJECT_NAME} raylib)
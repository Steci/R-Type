# cmake_minimum_required(VERSION 3.10)
# project(engine)

# set(CMAKE_BUILD_TYPE Release)

# set(CMAKE_CXX_STANDARD 20)
# set(GRAPHICS GRAPHICS_API_OPENGL_43)
# set(OpenGL_GL_PREFERENCE GLVND)

# include(../cmake/Findraylib.cmake)

# file(GLOB ENGINE_SOURCES "src/*.cpp" "main.cpp")

# add_library(EngineLib STATIC ${ENGINE_SOURCES})

# if(CMAKE_COMPILER_IS_GNUCXX)
#   add_compile_options(-Wall -Wextra -g3)
# endif(CMAKE_COMPILER_IS_GNUCXX)

# if (WIN32)
#     add_compile_options(-Wall)
#     set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
# endif(WIN32)

# add_executable(${PROJECT_NAME} ${ENGINE_SOURCES})

# include_directories(${PROJECT_SOURCE_DIR}/include)
# list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/include")
# target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDES})

# target_link_libraries(${PROJECT_NAME} raylib)

cmake_minimum_required(VERSION 3.10)
project(engine)


if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -Wextra -g3)
endif(CMAKE_COMPILER_IS_GNUCXX)

if (WIN32)
    add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
    #set_target_properties (indie_studio.exe PROPERTIES PREFIX "./build/")
endif(WIN32)

# ADD_LIBRARY(MyStaticLib STATIC)

# find_package(sys REQUIRED)

# find_package(netinet REQUIRED)

file(GLOB SOURCES "main.cpp" "src/*.cpp")
add_executable(engine ${SOURCES})

list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/include")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(engine PUBLIC ${EXTRA_INCLUDES})

add_custom_command(TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:engine> ${CMAKE_SOURCE_DIR}
)
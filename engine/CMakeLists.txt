cmake_minimum_required(VERSION 3.10)
set(raylib_DIR "~/chasfory/raylib/cmake/raylib-config.cmake")
find_package(raylib REQUIRED)
project(engine)

if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -Wextra -g3)
endif(CMAKE_COMPILER_IS_GNUCXX)

if (WIN32)
    add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
    #set_target_properties (indie_studio.exe PROPERTIES PREFIX "./build/")
endif(WIN32)

set(LIBRARY_NAME engine_lib)

set(CMAKE_CXX_STANDARD 20)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(OpenGL_GL_PREFERENCE GLVND)

include_directories(./include)

set(SOURCE_FILES
    ./src/Component.cpp
    ./src/Entity.cpp
    ./src/main.cpp
    ./src/System.cpp
)

add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

if(CMAKE_COMPILER_IS_GNUCXX)
  add_custom_command(TARGET ${LIBRARY_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${CMAKE_CURRENT_BINARY_DIR}/lib${LIBRARY_NAME}.so
      ${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}.so
  )
endif(CMAKE_COMPILER_IS_GNUCXX)

if (WIN32)
  add_custom_command(TARGET ${LIBRARY_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}.dll
      ${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}.dll
  )
endif(WIN32)

target_link_libraries(${LIBRARY_NAME} raylib)
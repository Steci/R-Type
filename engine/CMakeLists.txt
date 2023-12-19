cmake_minimum_required(VERSION 3.10)
project(engine)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -g3 -fPIC)
endif(CMAKE_COMPILER_IS_GNUCXX)

if (WIN32)
    add_compile_options(-Wall -fPIC)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
    #set_target_properties (indie_studio.exe PROPERTIES PREFIX "./build/")
endif(WIN32)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(LIBRARY_NAME engine_lib.so)
endif(CMAKE_COMPILER_IS_GNUCXX)
if (WIN32)
  set(LIBRARY_NAME engine_lib.dll)
endif(WIN32)

set(CMAKE_CXX_STANDARD 20)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(OpenGL_GL_PREFERENCE GLVND)

# Ajouter le chemin vers le fichier CMake de raylib
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Utiliser vcpkg pour trouver raylib
find_package(raylib CONFIG REQUIRED)

include_directories(./include ./include/Utils)

set(SOURCE_PATH ./src)

set(SOURCE_FILES
<<<<<<< HEAD
    ./src/Component.cpp
    ./src/Entity.cpp
    ./src/main.cpp
    ./src/System.cpp
    ./src/ResourcesManager.cpp
=======
    Component.cpp
    Entity.cpp
    main.cpp
    System.cpp
>>>>>>> 6876d0fa7935fc4a509b6215cd49870bbbee7f6e
)

set(SOURCE_FILES_PATH "")
foreach(SOURCE_FILE ${SOURCE_FILES})
    list(APPEND SOURCE_FILES_PATH ${SOURCE_PATH}/${SOURCE_FILE})
endforeach(SOURCE_FILE)

add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILES_PATH} ${HEADER_FILES})

add_custom_command(TARGET ${LIBRARY_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:${LIBRARY_NAME}>
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${LIBRARY_NAME} PRIVATE raylib)

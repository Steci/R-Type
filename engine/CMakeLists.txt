cmake_minimum_required(VERSION 3.22)
project(engine)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 20)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(OpenGL_GL_PREFERENCE GLVND)

# Liste des fichiers source de la bibliothèque
set(SOURCES src/ecs.cpp)


include(../cmake/Findraylib.cmake)

if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -Wextra -g3)
endif(CMAKE_COMPILER_IS_GNUCXX)

# Recherche de raylib
# find_package(raylib REQUIRED)

# Crée la bibliothèque statique
add_library(engine STATIC ${SOURCES})

# Inclut les fichiers d'en-tête de raylib
target_include_directories(engine PRIVATE ${raylib_INCLUDE_DIRS})
include_directories(include)

# Lie les bibliothèques raylib
target_link_libraries(engine PRIVATE ${raylib_LIBRARIES})

if (WIN32)
    add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
    #set_target_properties (indie_studio.exe PROPERTIES PREFIX "./build/")
elseif(APPLE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
endif(WIN32)


## set(CMAKE_BUILD_TYPE Release)
## 
## set(CMAKE_CXX_STANDARD 20)
## set(GRAPHICS GRAPHICS_API_OPENGL_43)
## set(OpenGL_GL_PREFERENCE GLVND)
## 
## include(cmake/Findraylib.cmake)
## include(cmake/FindYMLlib.cmake)
## 
## if(CMAKE_COMPILER_IS_GNUCXX)
##   add_compile_options(-Wall -Wextra -g3)
## endif(CMAKE_COMPILER_IS_GNUCXX)
## 
## if (WIN32)
##     add_compile_options(-Wall)
##     set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
##     #set_target_properties (indie_studio.exe PROPERTIES PREFIX "./build/")
## endif(WIN32)



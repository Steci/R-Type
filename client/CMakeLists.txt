cmake_minimum_required(VERSION 3.22)
project(client)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(OpenGL_GL_PREFERENCE GLVND)

# Liste des fichiers source de la bibliothèque
set(SOURCES src/main.cpp)

# Intégration avec Vcpkg (ajustez le chemin vers vcpkg selon votre installation)
# if (WIN32)
#     set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "")
# elseif (APPLE)
#     set(VCPKG_TARGET_TRIPLET "x64-osx" CACHE STRING "")
# else()  # Linux
#     set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "")
# endif()

include(../cmake/Findraylib.cmake)

if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -Wextra -g3)
endif(CMAKE_COMPILER_IS_GNUCXX)

# Recherche de raylib
# find_package(raylib REQUIRED)

include_directories(include)

# Ajoutez ici votre exécutable
add_executable(rtype src/main.cpp)  # Ajoutez tous les fichiers source nécessaires pour votre exécutable

if (WIN32)
    add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
    #set_target_properties (indie_studio.exe PROPERTIES PREFIX "./build/")
elseif(APPLE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
endif(WIN32)

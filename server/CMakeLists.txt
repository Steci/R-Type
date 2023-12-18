cmake_minimum_required(VERSION 3.22)
project(server)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(OpenGL_GL_PREFERENCE GLVND)



if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -Wextra -g3)
endif(CMAKE_COMPILER_IS_GNUCXX)


include_directories(include)
# target_link_libraries(server pthread)

# Ajoutez ici votre exécutable
add_executable(server main.cpp src/ErrorHandling.cpp src/Server.cpp src/Client.cpp src/Network.cpp)  # Ajoutez tous les fichiers source nécessaires pour votre exécutable


if (WIN32)
    add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
    #set_target_properties (indie_studio.exe PROPERTIES PREFIX "./build/")
elseif(APPLE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
endif(WIN32)

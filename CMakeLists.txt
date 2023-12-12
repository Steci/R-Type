cmake_minimum_required(VERSION 3.28)

# Utiliser une variable pour spécifier le chemin du fichier toolchain de Vcpkg
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Utiliser une variable pour spécifier le générateur CMake
set(CMAKE_GENERATOR "Unix Makefiles" CACHE STRING "CMake generator")

project(HelloWorld)

# Utiliser find_package avec le nom de la bibliothèque fmt sans CONFIG
find_package(fmt REQUIRED)

# Créer une cible exécutable HelloWorld avec le fichier source helloworld.cpp
add_executable(HelloWorld helloworld.cpp)

# Lier la bibliothèque fmt::fmt à la cible HelloWorld
target_link_libraries(HelloWorld PRIVATE fmt::fmt)

# Copier l'exécutable dans le répertoire source après la construction
add_custom_command(TARGET HelloWorld POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:HelloWorld> ${CMAKE_SOURCE_DIR}
)

cmake_minimum_required(VERSION 3.20.0)
project(Rtype)


set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OpenGL_GL_PREFERENCE GLVND)

# Définit le fichier de chaîne d'outils de vcpkg
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# include path
# use c function
# cast dynamic and static

#set(CMAKE_TOOLCHAIN_FILE "C:/Users/malek/Downloads/vcpkg-master/vcpkg-master/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")


# Configuration du générateur CMake en fonction du système d'exploitation
if(WIN32)
    set(CMAKE_GENERATOR "Visual Studio 17 2022" CACHE STRING "CMake generator" FORCE)
    set(VCPKG_INSTALLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed" CACHE STRING "")
elseif(APPLE)
    set(CMAKE_GENERATOR "Xcode" CACHE STRING "CMake generator" FORCE)
    set(VCPKG_INSTALLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed" CACHE STRING "")
else()
    set(CMAKE_GENERATOR "Unix Makefiles" CACHE STRING "CMake generator")
    set(VCPKG_INSTALLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed" CACHE STRING "")
endif()


list(APPEND CMAKE_PREFIX_PATH "${VCPKG_INSTALLED_DIR}")

# Configuration spécifique à GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -g3)
endif()

# Configuration spécifique à Windows
if(WIN32)
    add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
endif()

# Configuration de vcpkg
if(WIN32)
    set(VCPKG_TARGET_TRIPLET x64-windows)
elseif(APPLE)
    set(VCPKG_TARGET_TRIPLET x64-osx)
else()
    set(VCPKG_TARGET_TRIPLET x64-linux)
endif()

set(CMAKE_PREFIX_PATH "vcpkg_installed/${VCPKG_TARGET_TRIPLET}" CACHE STRING "Vcpkg prefix path" FORCE)



find_package(raylib CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)



add_subdirectory(engine)
#add_subdirectory(client)
add_subdirectory(server)











































































# Configuration des tests
#enable_testing()

# Ajouter le sous-projet pour les tests
#add_subdirectory(tests)

# Sous-projets
#add_subdirectory(client)
#add_subdirectory(server)



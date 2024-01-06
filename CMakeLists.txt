cmake_minimum_required(VERSION 3.20.0)
project(Rtype)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OpenGL_GL_PREFERENCE GLVND)

# Définit le fichier de chaîne d'outils de vcpkg
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Configuration du générateur CMake en fonction du système d'exploitation
if(WIN32)
    set(CMAKE_GENERATOR "Visual Studio 16 2019" CACHE STRING "CMake generator" FORCE)
    set(VCPKG_INSTALLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed" CACHE STRING "")
elseif(APPLE)
    set(CMAKE_GENERATOR "Xcode" CACHE STRING "CMake generator" FORCE)
    set(VCPKG_INSTALLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed" CACHE STRING "")
else()
    set(CMAKE_GENERATOR "Unix Makefiles" CACHE STRING "CMake generator")
    set(VCPKG_INSTALLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed" CACHE STRING "")
endif()


list(APPEND CMAKE_PREFIX_PATH "${VCPKG_INSTALLED_DIR}")

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -g3)
endif()

if(WIN32)
    #add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
endif()

if(WIN32)
    set(VCPKG_TARGET_TRIPLET x64-windows)
elseif(APPLE)
    set(VCPKG_TARGET_TRIPLET x64-osx)
else()
    set(VCPKG_TARGET_TRIPLET x64-linux)
endif()

set(CMAKE_PREFIX_PATH "vcpkg_installed/${VCPKG_TARGET_TRIPLET}" CACHE STRING "Vcpkg prefix path" FORCE)



# Engine
project(engine)
file(GLOB ENGINE_SOURCES "engine/src/*.cpp" "engine/main.cpp")

add_library(EngineLib STATIC ${ENGINE_SOURCES})

add_executable(${PROJECT_NAME} ${ENGINE_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/engine/include)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/engine/include")
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDES})

# Utiliser find_package pour trouver la bibliothèque raylib
find_package(raylib CONFIG REQUIRED)
target_link_libraries(engine PRIVATE raylib)



# Server
project(server_build)

# Ajouter le répertoire d'installation de Vcpkg
file(GLOB SOURCES "server/main.cpp" "server/src/*.cpp")# "engine/src/*.cpp" "engine/include/*.hpp")

add_executable(server_build ${SOURCES})

list(APPEND SERVER_EXTRA_INCLUDES "server/include")# "engine/include")
target_include_directories(server_build PUBLIC ${EXTRA_INCLUDES} ${SERVER_EXTRA_INCLUDES})


target_link_libraries(server_build PRIVATE pthread)
target_link_libraries(server_build PRIVATE engineLib raylib)

# Utiliser find_package pour trouver la bibliothèque fmt
find_package(fmt CONFIG REQUIRED)
target_link_libraries(server_build PRIVATE fmt::fmt)

# Utiliser find_package pour trouver la bibliothèque raylib
find_package(raylib CONFIG REQUIRED)
target_link_libraries(server_build PRIVATE raylib)

add_custom_command(TARGET server_build POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:server_build> ${CMAKE_SOURCE_DIR}
)




# Client
project(client_build)

file(GLOB SOURCES "client/main.cpp" "client/src/*.cpp")

add_executable(client_build ${SOURCES})

list(APPEND CLIENT_EXTRA_INCLUDES "client/include")

target_include_directories(client_build PUBLIC ${EXTRA_INCLUDES} ${CLIENT_EXTRA_INCLUDES})
target_link_libraries(client_build PRIVATE engineLib raylib)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(client_build PRIVATE raylib)

add_custom_command(TARGET client_build POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:client_build> ${CMAKE_SOURCE_DIR}
)


project(server_build)

# Ajouter le répertoire d'installation de Vcpkg

file(GLOB SOURCES "main.cpp" "src/*.cpp")# "engine/src/*.cpp" "engine/include/*.hpp")

add_executable(server_build ${SOURCES})

list(APPEND EXTRA_INCLUDES "include")# "engine/include")
target_include_directories(server_build PUBLIC ${EXTRA_INCLUDES})


target_link_libraries(server_build PRIVATE pthread)
target_link_libraries(server_build PRIVATE "../engine/engineLib" raylib)

# Utiliser find_package pour trouver la bibliothèque fmt
target_link_libraries(server_build PRIVATE fmt::fmt)

# Utiliser find_package pour trouver la bibliothèque raylib
target_link_libraries(server_build PRIVATE raylib)


add_custom_command(TARGET server_build POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:server_build> ${CMAKE_SOURCE_DIR}
)



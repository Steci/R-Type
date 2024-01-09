
project(lib_engine)
file(GLOB ENGINE_SOURCES "src/*.cpp")

add_library(EngineLib STATIC ${ENGINE_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/include)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/include")
target_include_directories(EngineLib PUBLIC ${EXTRA_INCLUDES})

# Vous ne devriez pas utiliser add_executable pour un projet lib_engine.
# Si vous voulez créer un exécutable, utilisez un autre nom de projet.

# Utiliser find_package pour trouver la bibliothèque raylib
target_link_libraries(EngineLib PRIVATE raylib)






project(EngineLib)

file(GLOB ENGINE_SOURCES
    "src/Entity.cpp"
    "src/Network.cpp"
    "src/System.cpp"
)

add_library(EngineLib STATIC ${ENGINE_SOURCES})
target_link_libraries(EngineLib PRIVATE raylib)

list(APPEND ENGINE_EXTRA_INCLUDES "include")
target_include_directories(EngineLib PUBLIC ${ENGINE_EXTRA_INCLUDES})
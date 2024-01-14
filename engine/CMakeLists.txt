project(EngineLib)

file(GLOB ENGINE_SOURCES
    "src/Entity.cpp"
    "src/Network.cpp"
    "src/System.cpp"
)

add_library(EngineLib STATIC ${ENGINE_SOURCES})
if(WIN32)
    target_link_libraries(EngineLib PRIVATE winmm.lib)
endif()
target_link_libraries(EngineLib PUBLIC raylib)

list(APPEND ENGINE_LIB_INCLUDES "include")
target_include_directories(EngineLib PUBLIC ${ENGINE_LIB_INCLUDES})

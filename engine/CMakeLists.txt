file(GLOB ENGINE_SOURCES "src/*.cpp" "main.cpp")

add_library(EngineLib STATIC ${ENGINE_SOURCES})
add_executable(engine ${ENGINE_SOURCES})

list(APPEND EXTRA_INCLUDES "include")
target_include_directories(engine PUBLIC ${EXTRA_INCLUDES})

#find_package(fmt CONFIG)
#find_package(raylib REQUIRED)

target_link_libraries(engine PRIVATE fmt)
target_link_libraries(engine PRIVATE raylib)

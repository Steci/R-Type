project(server)

file(GLOB SOURCES
    "src/Client.cpp"
    "src/Entity.cpp"
    "src/ErrorHandling.cpp"
    "src/Game.cpp"
    "src/Network.cpp"
    "src/Server.cpp"
    "src/System.cpp"
    "main.cpp"
)

add_executable(server_build ${SOURCES})

list(APPEND SERVER_EXTRA_INCLUDES "include")
target_include_directories(server_build PUBLIC ${SERVER_EXTRA_INCLUDES})

target_link_libraries(server_build PRIVATE raylib)
target_link_libraries(server_build PRIVATE pthread)
target_link_libraries(server_build PRIVATE EngineLib)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/engine)
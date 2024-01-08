project(client)

file(GLOB SOURCES
    "src/Client.cpp"
    "src/Entity.cpp"
    "src/ErrorHandling.cpp"
    "src/Game.cpp"
    "src/Interaction.cpp"
    "src/Network.cpp"
    "src/System.cpp"
    "main.cpp"
)

add_executable(client_build ${SOURCES})

list(APPEND CLIENT_EXTRA_INCLUDES "include")
target_include_directories(client_build PUBLIC ${CLIENT_EXTRA_INCLUDES})

target_link_libraries(client_build PRIVATE fmt)
target_link_libraries(client_build PRIVATE raylib)
target_link_libraries(client_build PRIVATE engineLib)

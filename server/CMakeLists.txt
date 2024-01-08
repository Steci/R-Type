project(server)

file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(server_build ${SOURCES})

list(APPEND SERVER_EXTRA_INCLUDES "include")
target_include_directories(server_build PUBLIC ${SERVER_EXTRA_INCLUDES})

target_link_libraries(server_build PRIVATE fmt)
target_link_libraries(server_build PRIVATE raylib)
target_link_libraries(server_build PRIVATE pthread)
target_link_libraries(server_build PRIVATE engineLib)

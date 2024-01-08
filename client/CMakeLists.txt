project(client_build)

file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(client_build ${SOURCES})

list(APPEND CLIENT_EXTRA_INCLUDES "include")

target_include_directories(client_build PUBLIC ${CLIENT_EXTRA_INCLUDES})
find_package(raylib CONFIG REQUIRED)
target_link_libraries(client_build PRIVATE engineLib raylib)

add_custom_command(TARGET client_build POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:client_build> ${CMAKE_SOURCE_DIR}
)

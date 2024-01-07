

project(client_build)

file(GLOB SOURCES "main.cpp" "src/*.cpp")

add_executable(client_build ${SOURCES})

list(APPEND EXTRA_INCLUDES "include")

target_include_directories(client_build PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(client_build PRIVATE "../engine/engineLib" raylib)

target_link_libraries(client_build PRIVATE raylib)

add_custom_command(TARGET client_build POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:client_build> ${CMAKE_SOURCE_DIR}
)


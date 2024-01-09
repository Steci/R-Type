project(client_build)

file(GLOB SOURCES "main.cpp" "src/*.cpp")

add_executable(client_build ${SOURCES})

list(APPEND EXTRA_INCLUDES "include")

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(client_build PRIVATE glfw)
target_link_libraries(client_build PRIVATE glfw3)
target_link_libraries(client_build PRIVATE raylib)

target_include_directories(client_build PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(client_build PRIVATE "${CMAKE_SOURCE_DIR}/engine/libEngineLib.a" raylib)



add_custom_command(TARGET client_build POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:client_build> ${CMAKE_SOURCE_DIR}
)


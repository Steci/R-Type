cmake_minimum_required(VERSION 3.10)
project(server)


# if(CMAKE_COMPILER_IS_GNUCXX)
#   add_compile_options(-Wall -Wextra -g3)
# endif(CMAKE_COMPILER_IS_GNUCXX)

# if (WIN32)
#     add_compile_options(-Wall)
#     set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./build/")
#     #set_target_properties (indie_studio.exe PROPERTIES PREFIX "./build/")
# endif(WIN32)

#ADD_LIBRARY(MyStaticLib STATIC

file(GLOB SOURCES "main.cpp" "src/*.cpp")
add_executable(server ${SOURCES})

list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/include")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(server PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(server pthread)

add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:server> ${CMAKE_SOURCE_DIR}
)
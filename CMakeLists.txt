
cmake_minimum_required(VERSION 3.20)
project(cs-project)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(cs-project
    src/main.c
    src/windowing.c
    src/game.c
    src/event_handler.c
    src/texture_handler.c
)

target_link_libraries(cs-project PRIVATE SDL2::SDL2)
target_link_libraries(cs-project PRIVATE SDL2_image::SDL2_image)

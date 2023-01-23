cmake_minimum_required(VERSION 3.10)

project (gol)

set(SOURCES
    src/board.cpp
    src/main.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
add_compile_options(-Wall -Wextra -pedantic -Werror)

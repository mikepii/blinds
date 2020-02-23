cmake_minimum_required(VERSION 3.13)
project(blinds)

set(CMAKE_C_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_subdirectory(util)
add_subdirectory(concurrency)
add_subdirectory(motor)

add_executable(blinds
        main.c
        )
target_link_libraries(blinds Blinds::Concurrency Blinds::Motor Blinds::Util)

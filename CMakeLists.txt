cmake_minimum_required(VERSION 3.13)
project(blinds)

set(CMAKE_C_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_subdirectory(buttons)
add_subdirectory(concurrency)
add_subdirectory(io)
add_subdirectory(raspberrypi)
add_subdirectory(motor)
add_subdirectory(util)

add_executable(blinds
        main.c
        )
target_link_libraries(blinds
        Blinds::Buttons
        Blinds::Concurrency
        Blinds::IO
        Blinds::Motor
        Blinds::RaspberryPi
        Blinds::Util
        )

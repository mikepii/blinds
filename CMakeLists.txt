cmake_minimum_required(VERSION 3.13)
project(blinds)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(wiringPi REQUIRED)

add_executable(blinds main.cpp)
target_link_libraries(blinds wiringPi)

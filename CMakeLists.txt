cmake_minimum_required(VERSION 3.15)
project(blinds)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(wiringPi)

add_executable(blinds main.cpp)
target_link_libraries(blinds wiringPi)

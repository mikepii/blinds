project(wiringPi C)

find_library(wiringPi_LIB wiringPi REQUIRED)

add_library(wiringPi INTERFACE)
target_link_libraries(wiringPi INTERFACE ${wiringPi_LIB})
target_include_directories(wiringPi INTERFACE include/)

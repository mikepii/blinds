project(blinds::raspberrypi)

find_package(wiringPi REQUIRED)

add_library(RaspberryPi STATIC
        raspi_motor.c
        )
add_library(Blinds::RaspberryPi ALIAS RaspberryPi)
target_link_libraries(RaspberryPi PRIVATE wiringPi)

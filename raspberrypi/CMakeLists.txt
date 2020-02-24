project(blinds::raspberrypi)

find_package(wiringPi REQUIRED)

add_library(RaspberryPi STATIC
        raspi.c
        raspi_buttons.c
        raspi_motor.c
        )
add_library(Blinds::RaspberryPi ALIAS RaspberryPi)
target_link_libraries(RaspberryPi
        PRIVATE Blinds::Util
        PRIVATE wiringPi
        )

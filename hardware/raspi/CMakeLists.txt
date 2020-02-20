project(blinds::hardware::raspi)

find_package(wiringPi REQUIRED)

add_library(Raspi STATIC
        raspi.c
        )
add_library(Blinds::Hardware::Raspi ALIAS Raspi)
target_link_libraries(Raspi
        PUBLIC Blinds::Hardware::Common
        PRIVATE wiringPi)

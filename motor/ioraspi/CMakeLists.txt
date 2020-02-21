project(blinds::motor::ioraspi)

find_package(wiringPi REQUIRED)

add_library(IORaspi STATIC
        raspi.c
        )
add_library(Blinds::Motor::IORaspi ALIAS IORaspi)
target_link_libraries(IORaspi
        PUBLIC Blinds::Motor::IO
        PRIVATE wiringPi)

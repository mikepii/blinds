project(blinds::motor::io)

add_library(MotorIO INTERFACE)
add_library(Blinds::Motor::IO ALIAS MotorIO)
target_include_directories(MotorIO INTERFACE include)

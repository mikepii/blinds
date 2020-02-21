project(blinds::motor::io)

add_library(IO INTERFACE)
add_library(Blinds::Motor::IO ALIAS IO)
target_include_directories(IO INTERFACE include)

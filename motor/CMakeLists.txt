project(blinds::motor)

add_subdirectory(io)
add_subdirectory(ioraspi)

add_library(Motor INTERFACE)
add_library(Blinds::Motor ALIAS Motor)
target_link_libraries(Motor INTERFACE Blinds::Motor::IORaspi)

project(blinds::motor)

add_subdirectory(io)

add_library(Motor STATIC
        position.c
        )
add_library(Blinds::Motor ALIAS Motor)
target_include_directories(Motor PUBLIC include)
target_link_libraries(Motor
        PUBLIC Blinds::Motor::IO
        PUBLIC Blinds::Util)

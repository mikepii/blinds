project(blinds::buttons)

add_subdirectory(io)

add_library(Buttons STATIC
        buttons.c
        )
add_library(Blinds::Buttons ALIAS Buttons)
target_include_directories(Buttons PUBLIC include)
target_link_libraries(Buttons
        PUBLIC Blinds::Motor
        PRIVATE Blinds::Buttons::IO)

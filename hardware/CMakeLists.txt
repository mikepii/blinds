project(blinds::hardware)

add_subdirectory(common)
add_subdirectory(raspi)

add_library(Hardware INTERFACE)
add_library(Blinds::Hardware ALIAS Hardware)
target_link_libraries(Hardware INTERFACE Blinds::Hardware::Raspi)

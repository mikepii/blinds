project(blinds::buttons::io)

add_library(ButtonsIO INTERFACE)
add_library(Blinds::Buttons::IO ALIAS ButtonsIO)
target_include_directories(ButtonsIO INTERFACE include)

project(blinds::io)

add_library(IO INTERFACE)
add_library(Blinds::IO ALIAS IO)
target_include_directories(IO INTERFACE include)

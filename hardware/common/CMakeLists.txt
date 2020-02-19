project(blinds::hardware::common)

add_library(Common INTERFACE)
add_library(Blinds::Hardware::Common ALIAS Common)
target_include_directories(Common INTERFACE include)

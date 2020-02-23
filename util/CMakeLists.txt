project(blinds::util)

add_library(Util INTERFACE)
add_library(Blinds::Util ALIAS Util)
target_include_directories(Util INTERFACE include)

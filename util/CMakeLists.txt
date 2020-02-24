project(blinds::util)

add_library(Util INTERFACE)
add_library(Blinds::Util ALIAS Util)
target_include_directories(Util INTERFACE include)

configure_file(include/blinds/util/configure.h.in include/blinds/util/configure.h)
target_include_directories(Util INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/include" @ONLY)

#[=======================================================================[.rst:
FindwiringPi
------------

Finds the wiringPi library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``wiringPi``
  The wiringPi library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``wiringPi_FOUND``
  True if the system has the wiringPi library.

#]=======================================================================]

# Find wiringPi include dir and library path.
find_path(wiringPi_INCLUDE_DIR NAMES wiringPi.h)
find_library(wiringPi_LIBRARY wiringPi)
# Set WiringPi_FOUND output variable and print error message if wiringPi is missing.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(wiringPi
        FOUND_VAR wiringPi_FOUND
        REQUIRED_VARS wiringPi_LIBRARY wiringPi_INCLUDE_DIR
        )
# Create imported target.
if(wiringPi_FOUND)
    add_library(wiringPi INTERFACE IMPORTED)
    target_include_directories(wiringPi INTERFACE "${wiringPi_INCLUDE_DIR}")
    target_link_libraries(wiringPi INTERFACE "${wiringPi_LIBRARY}")
endif()

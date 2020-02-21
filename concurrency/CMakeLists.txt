project(blinds::concurrency)

add_library(Concurrency STATIC
        eventloop.c
        )
add_library(Blinds::Concurrency ALIAS Concurrency)
target_include_directories(Concurrency PUBLIC include)

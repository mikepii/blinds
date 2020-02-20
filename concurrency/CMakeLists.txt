project(blinds::concurrency)

add_library(Concurrency STATIC
        concurrency.c
        )
add_library(Blinds::Concurrency ALIAS Concurrency)
target_include_directories(Concurrency PUBLIC include)

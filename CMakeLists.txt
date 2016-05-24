cmake_minimum_required(VERSION 2.8.4)
project(Data_Structure)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(SOURCE_FILES core/main.c
        core/linked_list.h
        core/error_codes.h
        core/circular_queue.h
        core/circular_queue.c
        unit_test/unit_test.c
        unit_test/random_generator.h
        unit_test/random_generator.c
        )
add_executable(Data_Structure ${SOURCE_FILES})


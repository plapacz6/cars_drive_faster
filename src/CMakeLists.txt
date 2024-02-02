cmake_minimum_required(VERSION 3.19)
project(cars_drive_faster)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
enable_testing()

list(APPEND obj_targets_list
    test_CMakeLists
)
foreach(obj_target IN LISTS obj_targets_list)
    list(APPEND obj_targets_src_list "${obj_target}.cpp")
    
endforeach()

foreach(obj_target obj_target_src 
        IN ZIP_LISTS 
        obj_targets_list obj_targets_src_list)
    add_library("${obj_target}" OBJECT "${obj_target_src}")
    target_include_directories("${obj_target}" PUBLIC ".")
    target_compile_options("${obj_target}" PUBLIC -g3 -Wall -pthread)
    target_link_libraries("${obj_target}" PUBLIC 
        pthread
    )    
endforeach()

add_subdirectory(test)
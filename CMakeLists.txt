cmake_minimum_required(VERSION 3.19)
project(cars_drive_faster)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
enable_testing()

add_subdirectory(src)

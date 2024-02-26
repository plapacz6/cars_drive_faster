cmake_minimum_required(VERSION 3.19)
project(cars_drive_faster)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
enable_testing()
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


list(APPEND obj_targets_list
    T_Rect
    PasteImgFunctions
    T_Obstacle    
    T_Car2 
    T_RoadHole 
    T_SteppeBush 
    T_Car1
    T_RoadLine
    T_Road
    T_Board
    T_GameDefs
    T_GameMutexes
    T_TimeController
    T_GameImages
    T_CLI
    T_CollisionChecker
    TBoardSector
    T_Car    
    T_VShiftUnit
    TOption
)
foreach(obj_target IN LISTS obj_targets_list)
    list(APPEND obj_targets_src_list "${obj_target}.cpp")    
endforeach()

foreach(obj_target obj_target_src 
        IN ZIP_LISTS 
        obj_targets_list obj_targets_src_list
)
    add_library("${obj_target}" OBJECT "${obj_target_src}")
    target_include_directories("${obj_target}" PUBLIC "./")
    target_compile_options("${obj_target}" PUBLIC -g3 -Wall -pthread)
    target_link_libraries("${obj_target}" PUBLIC 
        pthread
        ${OpenCV_LIBS}
    )    
endforeach()


list(APPEND targets_list 
    cars_drive_faster
)

foreach(target IN LISTS targets_list)
    add_executable("${target}" "${target}.cpp")
    target_include_directories("${target}" PRIVATE "./")
    target_compile_options("${target}" PRIVATE -g3 -Wall -pthread)
    target_link_libraries("${target}" PRIVATE 
        pthread
        ${obj_targets_list}
        ${OpenCV_LIBS}
    )    
endforeach()

add_subdirectory(test)

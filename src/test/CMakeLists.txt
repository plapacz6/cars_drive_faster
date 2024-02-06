cmake_minimum_required(VERSION 3.19)
project(cars_drive_faster)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
enable_testing()

list(APPEND targets_test_list
    T_Rect_test
    PasteImgFunctions_test
    T_Obstacle_test
    T_Car2_test
    T_RoadHole_test
    T_SteppeBush_test
    T_Car1_test
    T_RoadLine_test
    T_Road_test
    T_Board_test
    T_GameMutexes_test
    T_TimeController_test
    T_GameImages_test
    T_CLI_test
    T_CollisionChecker_test
    TBoardSector_test
    T_Car_test    
    T_VShiftUnit_test
    TOption_test
)
foreach(target_test IN LISTS targets_test_list)
    list(APPEND targets_test_src_list "${target_test}.cpp")
    
endforeach()

foreach(target_test target_test_src 
        IN ZIP_LISTS 
        targets_test_list targets_test_src_list)
    add_library("${target_test}" OBJECT "${target_test_src}")
    target_include_directories("${target_test}" PUBLIC "../")
    target_compile_options("${target_test}" PUBLIC -g3 -Wall -pthread)
    target_link_libraries("${target_test}" PUBLIC 
        ${obj_targets_list}    
        pthread
        ${OpenCV_LIBS}
        GTest::GTest 
        GTest::gtest_main
    )
    add_test("${target_test}_runner" "${target_test}")
endforeach()

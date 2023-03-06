cmake_minimum_required(VERSION 3.17)
project(pl6_game_engine_v2)

find_package(Catch2 3 REQUIRED)


add_executable(test_Rect_T test_Rect_T.cpp)
target_link_libraries(test_Rect_T PRIVATE $<TARGET_OBJECTS:Rect_T>)
target_link_libraries(test_Rect_T PRIVATE Catch2::Catch2WithMain)

add_executable(test_EngMove_T test_EngMove_T.cpp)
target_link_libraries(test_EngMove_T PRIVATE $<TARGET_OBJECTS:EngMove_T>)
target_link_libraries(test_EngMove_T PRIVATE Catch2::Catch2WithMain)

add_executable(test_game_obj_T test_game_obj_T.cpp)
target_link_libraries(test_game_obj_T PRIVATE $<TARGET_OBJECTS:game_obj_T>)
target_link_libraries(test_game_obj_T PRIVATE $<TARGET_OBJECTS:Rect_T>)
target_link_libraries(test_game_obj_T PRIVATE Catch2::Catch2WithMain)

add_executable(test_game_Vmovable_obj_T test_game_Vmovable_obj_T.cpp)
target_link_libraries(test_game_Vmovable_obj_T PRIVATE $<TARGET_OBJECTS:game_Vmovable_obj_T>)
target_link_libraries(test_game_Vmovable_obj_T PRIVATE $<TARGET_OBJECTS:EngMove_T>)
target_link_libraries(test_game_Vmovable_obj_T PRIVATE $<TARGET_OBJECTS:game_obj_T>)
target_link_libraries(test_game_Vmovable_obj_T PRIVATE $<TARGET_OBJECTS:Rect_T>)
target_link_libraries(test_game_Vmovable_obj_T PRIVATE Catch2::Catch2WithMain)

list(APPEND test_list
  test_Rect_T
  test_EngMove_T
  test_game_obj_T
  test_game_Vmovable_obj_T
)
foreach(test_target IN LISTS ${test_list})
  target_compile_options(${test_target} PRIVATE -Wall -g3)  
  target_compile_options(${test_target} PRIVATE -pthread)  
  #target_link_libraries(${test_target} PRIVATE Catch2::Catch2WithMain)
endforeach()


add_test(NAME test__Rect_T COMMAND test_Rect_T)
add_test(NAME test__EngMove_T COMMAND test_EngMove_T)
add_test(NAME test__game_obj_T COMMAND test_game_obj_T)
add_test(NAME test__game_Vmovable_obj_T COMMAND test_game_Vmovable_obj_T)


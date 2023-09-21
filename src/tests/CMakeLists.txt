cmake_minimum_required(VERSION 3.17)
project(pl6_game_engine_v2)

find_package(Catch2 3 REQUIRED)


add_executable(test_game_board_obj_T test_game_board_obj_T.cpp)
target_link_libraries(test_game_board_obj_T PRIVATE $<TARGET_OBJECTS:game_board_obj_T>)
target_link_libraries(test_game_board_obj_T PRIVATE $<TARGET_OBJECTS:Rect_T>)
target_link_libraries(test_game_board_obj_T PRIVATE $<TARGET_OBJECTS:game_obj_T>)
target_link_libraries(test_game_board_obj_T PRIVATE $<TARGET_OBJECTS:debug_view_T>)
target_link_libraries(test_game_board_obj_T PRIVATE $<TARGET_OBJECTS:board_T>)
#target_link_libraries(test_game_board_obj_T PRIVATE $<TARGET_OBJECTS:move_en_T>)
target_link_libraries(test_game_board_obj_T PRIVATE Catch2::Catch2WithMain)

list(APPEND test_list  
  test_game_board_obj_T
)
foreach(test_target IN LISTS ${test_list})
  target_compile_options(${test_target} PRIVATE -Wall -g3)  
  target_compile_options(${test_target} PRIVATE -pthread)  
  #target_link_libraries(${test_target} PRIVATE Catch2::Catch2WithMain)
endforeach()


add_test(NAME test__game_board_obj_T COMMAND test_game_board_obj_T)


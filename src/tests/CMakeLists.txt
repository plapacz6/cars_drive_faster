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

add_executable(test_move_en_T test_move_en_T.cpp)
target_link_libraries(test_move_en_T PRIVATE $<TARGET_OBJECTS:move_en_T>)
target_link_libraries(test_move_en_T PRIVATE $<TARGET_OBJECTS:game_board_obj_T>)
target_link_libraries(test_move_en_T PRIVATE $<TARGET_OBJECTS:Rect_T>)
target_link_libraries(test_move_en_T PRIVATE $<TARGET_OBJECTS:game_obj_T>)
target_link_libraries(test_move_en_T PRIVATE $<TARGET_OBJECTS:debug_view_T>)
target_link_libraries(test_move_en_T PRIVATE $<TARGET_OBJECTS:board_T>)
target_link_libraries(test_move_en_T PRIVATE Catch2::Catch2WithMain)

add_executable(test_check_collisions_en_T test_check_collisions_en_T.cpp)
target_link_libraries(test_check_collisions_en_T PRIVATE $<TARGET_OBJECTS:check_collisions_en_T>)
target_link_libraries(test_check_collisions_en_T PRIVATE $<TARGET_OBJECTS:game_collidable_obj_T>)
target_link_libraries(test_check_collisions_en_T PRIVATE $<TARGET_OBJECTS:move_en_T>)
target_link_libraries(test_check_collisions_en_T PRIVATE $<TARGET_OBJECTS:game_board_obj_T>)
target_link_libraries(test_check_collisions_en_T PRIVATE $<TARGET_OBJECTS:Rect_T>)
target_link_libraries(test_check_collisions_en_T PRIVATE $<TARGET_OBJECTS:game_obj_T>)
target_link_libraries(test_check_collisions_en_T PRIVATE $<TARGET_OBJECTS:debug_view_T>)
target_link_libraries(test_check_collisions_en_T PRIVATE $<TARGET_OBJECTS:board_T>)
target_link_libraries(test_check_collisions_en_T PRIVATE $<TARGET_OBJECTS:collision_def_T>)
target_link_libraries(test_check_collisions_en_T PRIVATE $<TARGET_OBJECTS:collision_type_T>)
target_link_libraries(test_check_collisions_en_T PRIVATE $<TARGET_OBJECTS:game_obj_category_T>)
target_link_libraries(test_check_collisions_en_T PRIVATE Catch2::Catch2WithMain)

list(APPEND test_list  
  test_game_board_obj_T
  test_move_en_T
  test_check_collisions_en_T
)
foreach(test_target IN LISTS test_list)
  message(${test_target})
  target_compile_options(${test_target} PRIVATE -Wall -g3)  
  target_compile_options(${test_target} PUBLIC -pthread)  
  #target_link_libraries(${test_target} PRIVATE Catch2::Catch2WithMain)  
  target_compile_definitions(${test_target} PUBLIC          
      $<$<CONFIG:Debug>:DEBUG>
      $<$<CONFIG:Debug>:PDEBUG_ON>
  )
endforeach()


add_test(NAME test__game_board_obj_T COMMAND test_game_board_obj_T)
add_test(NAME test__move_en_T COMMAND test_move_en_T)
add_test(NAME test__check_collisions_en_T COMMAND test_check_collisions_en_T)


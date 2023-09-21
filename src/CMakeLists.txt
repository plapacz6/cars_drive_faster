cmake_minimum_required(VERSION 3.17)
project(pl6_game_engine_v2)
find_library(NAME pthread)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(tests)
add_subdirectory(debug)

list(APPEND my_objects
  Rect_T
  board_T
  move_en_T
  #check_colissions_en_T
  game_obj_T
  game_board_obj_T
  #game_colidable_obj_T  
  debug_view_T
)
add_library(Rect_T OBJECT Rect_T.cpp)
add_library(board_T OBJECT board_T.cpp)
add_library(move_en_T OBJECT move_en_T.cpp)
#add_library(check_colissions_en_T OBJECT check_colissions_en_T.cpp)
add_library(game_obj_T OBJECT game_obj_T.cpp)
add_library(game_board_obj_T OBJECT game_board_obj_T.cpp)
#add_library(game_colidable_obj_T OBJECT game_colidable_obj_T.cpp)
add_library(debug_view_T OBJECT debug_view_T.cpp)

foreach(my_object IN LISTS ${my_objects})
  target_compile_options(${test_target} PRIVATE -Wall -g3)  
  target_compile_options(${my_object} PUBLIC -pthread)
endforeach()
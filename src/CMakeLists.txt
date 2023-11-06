cmake_minimum_required(VERSION 3.17)
project(pl6_game_engine_v2)
find_library(NAME pthread)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(tests)
add_subdirectory(debug)

add_library(Rect_T OBJECT Rect_T.cpp)
add_library(board_T OBJECT board_T.cpp)
add_library(move_en_T OBJECT move_en_T.cpp)
add_library(check_collisions_en_T OBJECT check_collisions_en_T.cpp)
add_library(game_obj_T OBJECT game_obj_T.cpp)
add_library(game_board_obj_T OBJECT game_board_obj_T.cpp)
add_library(game_collidable_obj_T OBJECT game_collidable_obj_T.cpp)
add_library(debug_view_T OBJECT debug_view_T.cpp)
add_library(collision_def_T OBJECT collision_def_T.cpp)
add_library(collision_type_T OBJECT collision_type_T.cpp)
add_library(game_obj_category_T OBJECT game_obj_category_T.cpp)

list(APPEND my_objects
  Rect_T
  board_T
  move_en_T  
  game_obj_T
  game_board_obj_T
  debug_view_T
  check_collisions_en_T
  game_collidable_obj_T  
  collision_def_T
  collision_type_T
  game_obj_category_T
)
foreach(my_object IN LISTS my_objects)
  message(${my_object})
  target_compile_options(${my_object} PRIVATE -Wall -g3)  
  target_compile_options(${my_object} PUBLIC -pthread)  
  target_compile_definitions(${my_object} PUBLIC          
      $<$<CONFIG:Debug>:DEBUG>
      $<$<CONFIG:Debug>:PDEBUG_ON>
  )
endforeach()
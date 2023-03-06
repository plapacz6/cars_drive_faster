cmake_minimum_required(VERSION 3.17)
project(pl6_game_engine_v2)
find_library(NAME pthread)

add_subdirectory(test)

list(APPEND my_objects
  Rect_T
  EngMove_T
  game_obj_T
  game_Vmovable_obj_T
)
add_library(Rect_T OBJECT Rect_T.cpp)
add_library(EngMove_T OBJECT EngMove_T.cpp)
add_library(game_obj_T OBJECT game_obj_T.cpp)
add_library(game_Vmovable_obj_T OBJECT game_Vmovable_obj_T.cpp)

foreach(my_object IN LISTS ${my_objects})
  target_compile_options(${test_target} PRIVATE -Wall -g3)  
  target_compile_options(${my_object} PUBLIC -pthread)
endforeach()
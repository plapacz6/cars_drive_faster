#include <catch2/catch_all.hpp>
#include "test_game_Vmovable_obj_T.h"

EngMove_T glob_em_y;

TEST_CASE("creating object"){
  game_Vmovable_obj_T gvmo;
  gvmo.vspeed = -2;
  REQUIRE(gvmo.vspeed == -2);
  game_Vmovable_obj_T gvmo2(glob_em_y);
  gvmo2.vspeed = 2;
  REQUIRE(gvmo2.vspeed == 2);
};
TEST_CASE("adding and movig"){
  
  glob_em_y.clear();

  game_Vmovable_obj_T gvmo1;
  gvmo1.pos.x = 1;
  gvmo1.pos.y = 2;
  gvmo1.pos.w = 3;
  gvmo1.pos.h = 5;
  gvmo1.vspeed = 2;
  
  game_Vmovable_obj_T gvmo2;
  gvmo2.pos.x = 5;
  gvmo2.pos.y = 6;
  gvmo2.pos.w = 7;
  gvmo2.pos.h = 8;
  gvmo2.vspeed = -8;

  glob_em_y.move();

  REQUIRE(gvmo1.pos.x == 1);
  REQUIRE(gvmo1.pos.y == 4);
  REQUIRE(gvmo1.pos.w == 3);
  REQUIRE(gvmo1.pos.h == 5);
  REQUIRE(gvmo1.vspeed == 2);

  REQUIRE(gvmo2.pos.x == 5);
  REQUIRE(gvmo2.pos.y == -2);
  REQUIRE(gvmo2.pos.w == 7);
  REQUIRE(gvmo2.pos.h == 8);
  REQUIRE(gvmo2.vspeed == -8);
}


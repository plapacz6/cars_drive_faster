#include <catch2/catch_all.hpp>
#include "test_game_obj_T.h"

TEST_CASE("creating object"){
  game_obj_T go;
  go.pos.x = 1;
  go.pos.y = 2;
  go.pos.w = 3;
  go.pos.h = 4;
  REQUIRE(go.pos.x == 1);
  REQUIRE(go.pos.y == 2);
  REQUIRE(go.pos.w == 3);
  REQUIRE(go.pos.h == 4);
};


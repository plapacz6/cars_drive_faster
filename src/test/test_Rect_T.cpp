//#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "test_Rect_T.h"

TEST_CASE("creation object"){
  Rect_T rect1;
  rect1.x = 1;
  rect1.y = 2;
  rect1.w = 3;
  rect1.h = 4;
  REQUIRE(rect1.x == 1);
  REQUIRE(rect1.y == 2);
  REQUIRE(rect1.w == 3);
  REQUIRE(rect1.h == 4);
}
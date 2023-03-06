#include <catch2/catch_all.hpp>
#include "test_EngMove_T.h"


TEST_CASE("creating object"){
  EngMove_T em_y;
};
TEST_CASE("adding and moving"){
  EngMove_T em_y;
  int st = 1;
  int sp = 2;
  em_y.register_to_process(&st, &sp);  
  em_y.move();
  REQUIRE(st == 3);
  sp = -4;
  em_y.move();
  REQUIRE(st == -1);
  em_y.move();
  REQUIRE(st == -5);
}
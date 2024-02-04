#include <gtest/gtest.h>

#include <iostream>
#include <thread>

#include "../T_GameMutexes.h"

using namespace std;
using namespace csfgame;

TEST(Suite01, Test01) {
    T_GameMutexes obj;
    //obj.set_(TTT);
    ASSERT_EQ(1, 1);
    //ASSERT_EQ(1, obj.get_());
}


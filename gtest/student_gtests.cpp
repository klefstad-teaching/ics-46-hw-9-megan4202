#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(LadderTest, edit_distance_withinTest) {
  // Test cases with only letter changes
  EXPECT_TRUE(edit_distance_within("car", "cat", 1));
  EXPECT_TRUE(edit_distance_within("bar", "car", 1));
  EXPECT_TRUE(edit_distance_within("can", "con", 1));
  EXPECT_FALSE(edit_distance_within("dog", "bag", 1));

  // Test cases with only insertions/deletions
  EXPECT_TRUE(edit_distance_within("anal", "canal", 1));
  EXPECT_TRUE(edit_distance_within("cheat", "chat", 1));
  EXPECT_TRUE(edit_distance_within("goat", "goatee", 2));
  EXPECT_FALSE(edit_distance_within("chat", "cheater", 2));

  // Test cases with letter changes and insertions/deletions
  EXPECT_TRUE(edit_distance_within("canary", "canal", 2));
  EXPECT_FALSE(edit_distance_within("goat", "goalie", 2));
  EXPECT_FALSE(edit_distance_within("cheat", "hat", 1));
}

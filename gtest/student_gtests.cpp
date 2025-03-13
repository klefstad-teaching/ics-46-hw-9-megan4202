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

TEST(LadderTest, is_adjacentTest) {
  EXPECT_TRUE(is_adjacent("bog", "log"));
  EXPECT_TRUE(is_adjacent("bog", "bag"));
  EXPECT_TRUE(is_adjacent("bog", "bot"));
  EXPECT_TRUE(is_adjacent("log", "blog"));
  EXPECT_TRUE(is_adjacent("barn", "bar"));
  EXPECT_TRUE(is_adjacent("long", "log"));
  EXPECT_TRUE(is_adjacent("bog", "bog"));
  EXPECT_TRUE(is_adjacent("wee", "woe"));
  EXPECT_FALSE(is_adjacent("blow", "show"));
  EXPECT_FALSE(is_adjacent("show", "shower"));
  EXPECT_FALSE(is_adjacent("blogs", "bog"));
}

TEST(LadderTest, generate_word_ladderTest) {
  verify_word_ladder();
}

TEST(DijkstrasTest, dijkstra_shortest_pathTest) {
  Graph G;
  vector<int> previous;
  vector<int> distances;
  vector<int> expectedDistances;
  vector<int> expectedShortestPath;
  file_to_graph("../src/small.txt", G);
  distances = dijkstra_shortest_path(G, 0, previous);
  expectedDistances = {0, 3, 6, 1};
  EXPECT_EQ(distances, expectedDistances);
  expectedShortestPath = {0, 3, 1};
  EXPECT_EQ(extract_shortest_path(distances, previous, 1), expectedShortestPath);
  expectedShortestPath = {0, 3, 1, 2};
  EXPECT_EQ(extract_shortest_path(distances, previous, 2), expectedShortestPath);
  expectedShortestPath = {0, 3};
  EXPECT_EQ(extract_shortest_path(distances, previous, 3), expectedShortestPath);
  expectedShortestPath = {0};
  EXPECT_EQ(extract_shortest_path(distances, previous, 0), expectedShortestPath);

  G.clear();
  file_to_graph("../src/medium.txt", G);
  distances = dijkstra_shortest_path(G, 0, previous);
  expectedDistances = {0, 5, 3, 12, 10, 2};
  EXPECT_EQ(distances, expectedDistances);
  expectedShortestPath = {0, 5, 2, 3};
  EXPECT_EQ(extract_shortest_path(distances, previous, 3), expectedShortestPath);
  expectedShortestPath = {0, 5, 4};
  EXPECT_EQ(extract_shortest_path(distances, previous, 4), expectedShortestPath);
}

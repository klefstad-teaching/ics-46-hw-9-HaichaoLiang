#include <gtest/gtest.h>
#include "ladder.h"
#include "dijkstras.h"

TEST(WordLadderTest, BasicWordLadders) {
    set<string> word_list;
    load_words(word_list, "words.txt");

    EXPECT_EQ(generate_word_ladder("cat", "dog", word_list).size(), 4);
    EXPECT_EQ(generate_word_ladder("marty", "curls", word_list).size(), 6);
    EXPECT_EQ(generate_word_ladder("code", "data", word_list).size(), 6);
    EXPECT_EQ(generate_word_ladder("work", "play", word_list).size(), 6);
    EXPECT_EQ(generate_word_ladder("sleep", "awake", word_list).size(), 8);
    EXPECT_EQ(generate_word_ladder("car", "cheat", word_list).size(), 4);
}

TEST(WordLadderTest, NoLadderAvailable) {
    set<string> word_list;
    load_words(word_list, "words.txt");
    EXPECT_EQ(generate_word_ladder("abcd", "wxyz", word_list).size(), 0);
}

TEST(DijkstraTest, SmallGraph) {
    Graph G;
    G.numVertices = 4;
    G.resize(4);
    G[0].push_back(Edge(0, 1, 3));
    G[0].push_back(Edge(0, 3, 1));
    G[1].push_back(Edge(1, 2, 3));
    G[3].push_back(Edge(3, 1, 1));
    G[3].push_back(Edge(3, 2, 2));

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 3);
    EXPECT_EQ(distances[2], 6);
    EXPECT_EQ(distances[3], 1);
}

TEST(DijkstraTest, NoPath) {
    Graph G;
    G.numVertices = 3;
    G.resize(3);
    G[0].push_back(Edge(0, 1, 5));

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 5);
    EXPECT_EQ(distances[2], INF);
}


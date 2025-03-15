#include <gtest/gtest.h>
#include "../src/dijkstras.h"
#include "../src/ladder.h"
#include <sstream>

TEST(DijkstraTest, ShortestPathBasic) {
    Graph G;
    G.numVertices = 4;
    G.resize(4);
    
    G[0].push_back({0, 1, 3});
    G[0].push_back({0, 2, 1});
    G[1].push_back({1, 3, 1});
    G[2].push_back({2, 3, 5});

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[1], 3);
    EXPECT_EQ(distances[2], 1);
    EXPECT_EQ(distances[3], 4);
}

TEST(DijkstraTest, NoPathAvailable) {
    Graph G;
    G.numVertices = 3;
    G.resize(3);

    G[0].push_back({0, 1, 2});

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[2], INF);
}

TEST(DijkstraTest, ExtractShortestPath) {
    Graph G;
    G.numVertices = 5;
    G.resize(5);

    G[0].push_back({0, 1, 1});
    G[1].push_back({1, 2, 2});
    G[2].push_back({2, 3, 3});
    G[3].push_back({3, 4, 4});

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    vector<int> path = extract_shortest_path(distances, previous, 4);
    vector<int> expected_path = {0, 1, 2, 3, 4};

    EXPECT_EQ(path, expected_path);
}

TEST(WordLadderTest, BasicLadder) {
    set<string> word_list = {"cat", "bat", "bit", "bot", "bog", "dog"};
    
    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    vector<string> expected_ladder = {"cat", "bat", "bot", "bog", "dog"};

    EXPECT_EQ(ladder, expected_ladder);
}

TEST(WordLadderTest, NoPossibleLadder) {
    set<string> word_list = {"cat", "bat", "bit", "dog"};

    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    
    EXPECT_TRUE(ladder.empty());
}

TEST(WordLadderTest, SameWordNoLadder) {
    set<string> word_list = {"cat", "bat", "bit", "dog"};

    vector<string> ladder = generate_word_ladder("cat", "cat", word_list);
    
    EXPECT_TRUE(ladder.empty());
}

TEST(WordLadderTest, PrintWordLadder) {
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    vector<string> ladder = {"cat", "bat", "bit", "bot", "bog", "dog"};
    print_word_ladder(ladder);

    std::cout.rdbuf(old_cout);

    EXPECT_EQ(output.str(), "Word ladder found: cat bat bit bot bog dog \n");
}

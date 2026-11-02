#include <gtest/gtest.h>
#include "Trie.hpp"

//using namespace test;

TEST(TrieSimpleTest, TrieCreation)
{
    Trie trie;
}

TEST(TrieSimpleTest, TrieOneInsertOneFound)
{
    Trie trie;

    trie.insert("some");

    ASSERT_EQ(1, trie.countWithKey("so"));
    ASSERT_EQ(1, trie.countWithKey("some"));
}

TEST(TrieSimpleTest, TrieOneInsertOneNonFound)
{
    Trie trie;

    trie.insert("some");

    ASSERT_EQ(0, trie.countWithKey("soe"));
}

TEST(TrieSimpleTest, TrieTwoInsertOneFound)
{
    Trie trie;

    trie.insert("some");
    trie.insert("somel");

    ASSERT_EQ(1, trie.countWithKey("somel"));
    ASSERT_EQ(2, trie.countWithKey("some"));
}

TEST(TrieSimpleTest, TrieInvalidData)
{
    Trie trie;

    trie.insert(nullptr);
    trie.insert(std::string());

    ASSERT_EQ(0, trie.countWithKey(nullptr));
    ASSERT_EQ(0, trie.countWithKey(std::string()));
    ASSERT_EQ(0, trie.countWithKey(""));
    ASSERT_EQ(0, trie.countWithKey("s"));
}

TEST(TrieSimpleTest, TrieThreeWithSameSubstring)
{
    Trie trie;

    trie.insert("some");
    trie.insert("somel");
    trie.insert("somela");

    ASSERT_EQ(3, trie.countWithKey("some"));
    ASSERT_EQ(2, trie.countWithKey("somel"));
}

TEST(TrieSimpleTest, InsertSameOneTwoTimes)
{
    Trie trie;

    trie.insert("some");
    trie.insert("some");

    ASSERT_EQ(1, trie.countWithKey("some"));
}

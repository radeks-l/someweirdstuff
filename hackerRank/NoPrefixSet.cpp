#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

constexpr int ALPHABET_SIZE = 'j' - 'a' + 1;

struct TrieNode {
    TrieNode() {
        for (auto &it: nodes)
            it = nullptr;
        isLeave = false;
    }
    TrieNode *nodes[ALPHABET_SIZE];
    bool isLeave;
};

int char2idx(char c) {
    return static_cast<int>(c) - static_cast<int>('a');
}

bool insert(TrieNode *root, const char *key) {
    int newNodes = 0;
    while (*key != '\0') {
        int idx = char2idx(*key);
        if (nullptr == root->nodes[idx]) {
            root->nodes[idx] = new TrieNode;
            newNodes++;
        } else {
            if (true == root->nodes[idx]->isLeave) {
                return false;
            }
        }
        root = root->nodes[idx];
        key++;
    }
    root->isLeave = true;
    if (newNodes == 0)
        return false;
    return true;
}

int main() {
    int N = 0, res = 0;
    char word[60];
    res = scanf("%d\n", &N);
    TrieNode *root = new TrieNode;
    while (N-- > 0) {
        res = scanf("%s\n", word);
        if (false == insert(root, word))
            break;
    }
    if (N == -1)
        printf("GOOD SET\n");
    else
        printf("BAD SET\n%s\n", word);
    return 0;
}


#include "Trie.hpp"

#include <iostream>

int main() {
    int N = 0;
    char operation[25], word[25];
    int r = scanf("%d\n", &N);
    Trie trie;
    for (int it = 0; it < N; ++it) {
        r = scanf("%s %s\n", operation, word);
        if (operation[0] == 'a') {
            trie.insert(word);
        } else {
            printf("%d\n", trie.countWithKey(word));
        }
    }
    return 0;
}


#include <cstdio>

struct Node {
    int data;
    Node *left;
    Node *right;
};

int main(void) {
    int N = 0, a = 0, b = 0, T = 0;
    std::scanf("%d\n", &N);
    Node *root = new Node{1, nullptr, nullptr};
    Node *left = nullptr;
    Node *right = nullptr;

    right = root;
    for (int it = 0; it < N; ++it) {
        std::scanf("%d %d\n", &a, &b);
        auto *l = new Node{a, nullptr, nullptr};
        auto *r = new Node{b, nullptr, nullptr};
        right->left = l;
        right->right = r;
    }
    return 0;
}

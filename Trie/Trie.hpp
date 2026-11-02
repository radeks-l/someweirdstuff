#include <string>
#include <cstring>

class Trie {

    static const int ALPHABET_SIZE = 26;

    struct TrieNode {
        TrieNode() {
            for(auto &it: nodes) {
                it = nullptr;
            }
            isLeave = false;
            cntForThis = 0;
        }
        TrieNode *nodes[ALPHABET_SIZE];
        bool isLeave;
        int cntForThis;
    };

public:

    Trie(): root(new TrieNode) {}

    ~Trie() {
        cleanNode(root);
    }

    void insert(const std::string &data) {
        if (false == data.empty())
            insert(data.c_str());
    }

    void insert(const char *data) {
        if (nullptr == data)
            return;
        int idx = 0;
        TrieNode *leave = root;
        while ('\0' != *data) {
            idx = char2idx(*data);
            if (nullptr == leave->nodes[idx]) {
                leave->nodes[idx] = new TrieNode;
            }
            leave->nodes[idx]->cntForThis++;
            leave = leave->nodes[idx];
            data++;
        }
        leave->isLeave = true;
    }

    int countWithKey(const std::string &key) {
        if (false == key.empty())
            return countWithKey(key.c_str());
        return 0;
    }

    int countWithKey(const char *key) {
        int cnt = 0;
        TrieNode *node = find(key);
        if (nullptr != node) {
            return node->cntForThis;
            /*
            cnt = countUnderNode(node);
            if (node->isLeave)
                cnt++;
            */
        }
        return cnt;
    }
private:
    TrieNode *root;

    inline int char2idx(char c) {
        return static_cast<int>(c) - static_cast<int>('a');
    }

    TrieNode *find(const char *key) {
        if (nullptr == key || nullptr == root)
            return nullptr;
        TrieNode *found = root;
        int idx;
        while ('\0' != *key) {
            idx = char2idx(*key);
            if (nullptr == found->nodes[idx])
                return nullptr;
            else
                found = found->nodes[idx];
            key++;
        }
        return found;
    }

    void cleanNode(TrieNode *node) {
        if (nullptr != node) {
            for (auto it: node->nodes)
                cleanNode(it);
            delete node;
        }
    }

    int countUnderNode(const TrieNode *node) const {
        int cnt = 0;
        for (auto it: node->nodes) {
            if (nullptr != it) {
                if (true == it->isLeave)
                    cnt++;
                cnt += countUnderNode(it);
            }
        }
        return cnt;
    }
};


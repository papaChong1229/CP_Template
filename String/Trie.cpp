#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    unordered_map<int, Node*> children;
    int cnt = 0;
    bool isEnd = false;
};

class Trie {
private:
    Node* root;

public:
    Trie() {
        root = new Node();
    }

    void insert(const string& s) {
        Node* curr = root;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int j = s[i] - 'a';
            if (!curr->children.contains(j)) {
                curr->children[j] = new Node();
            }
            curr = curr->children[j];
            curr->cnt++;
        }
        curr->isEnd = true;
    }

    void erase(const string& s) {
        Node* curr = root;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int j = s[i] - 'a';
            if (!curr->children.contains(j)) {
                curr->children[j] = new Node();
            }
            curr = curr->children[j];
            curr->cnt--;
        }
    }

    int search(const string& s) {
        Node* curr = root;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int j = s[i] - 'a';
            if (!curr->children.contains(j)) {
                return 0;
            }
            curr = curr->children[j];
        }
        return curr->isEnd;
    }

    int searchPrefix(const string& s) {
        Node* curr = root;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int j = s[i] - 'a';
            if (!curr->children.contains(j)) {
                return 0;
            }
            curr = curr->children[j];
        }
        return curr->cnt;
    }
};
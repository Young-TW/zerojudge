#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;

struct Node {
    int child[26];
    int child_count;
    bool is_end;
    Node() {
        memset(child, -1, sizeof(child));
        child_count = 0;
        is_end = false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<string> words;
        words.reserve(N);
        string word;
        size_t total_len = 0;
        for (int i = 0; i < N; ++i) {
            cin >> word;
            words.push_back(word);
            total_len += word.size();
        }
        
        vector<Node> trie;
        trie.reserve(total_len + 1);
        trie.emplace_back(); // root at index 0
        
        // Build trie
        for (const string& w : words) {
            int u = 0;
            for (char ch : w) {
                int c = ch - 'a';
                if (trie[u].child[c] == -1) {
                    trie[u].child[c] = trie.size();
                    trie[u].child_count++;
                    trie.emplace_back();
                }
                u = trie[u].child[c];
            }
            trie[u].is_end = true;
        }
        
        long long total_keystrokes = 0;
        for (const string& w : words) {
            int u = 0;
            int keystrokes = 0;
            for (size_t i = 0; i < w.size(); ++i) {
                int c = w[i] - 'a';
                if (i == 0) {
                    keystrokes = 1; // first letter always manual
                } else {
                    // check if previous prefix forces the next character
                    if (trie[u].child_count == 1 && !trie[u].is_end) {
                        // automatic, no keystroke
                    } else {
                        keystrokes++;
                    }
                }
                u = trie[u].child[c];
            }
            total_keystrokes += keystrokes;
        }
        
        // Compute average * 100 with rounding (half up)
        long long avg100 = (total_keystrokes * 100 + N / 2) / N;
        printf("%lld.%02lld\n", avg100 / 100, avg100 % 100);
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int nxt[26];
    int cnt;
    Node() {
        memset(nxt, -1, sizeof(nxt));
        cnt = 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (!(cin >> N)) return 0;
    vector<string> names(N);
    for (int i = 0; i < N; ++i) cin >> names[i];

    // Build Trie and count prefixes
    vector<Node> trie;
    trie.reserve(1000000);
    trie.emplace_back();               // root at index 0

    for (const string &s : names) {
        int cur = 0;
        for (char ch : s) {
            int id = ch - 'A';
            if (trie[cur].nxt[id] == -1) {
                trie[cur].nxt[id] = (int)trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].nxt[id];
            ++trie[cur].cnt;            // this prefix appears in one more name
        }
    }

    // Answer each name
    for (const string &s : names) {
        long long sum = 0;
        int cur = 0;
        for (char ch : s) {
            int id = ch - 'A';
            cur = trie[cur].nxt[id];
            sum += trie[cur].cnt;
        }
        sum -= (long long)s.size();    // remove the self‑count for each prefix
        cout << sum << '\n';
    }
    return 0;
}

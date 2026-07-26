#include <iostream>
#include <vector>
using namespace std;

struct Trie {
    struct Node {
        int child[2];
        int cnt;
        Node() {
            child[0] = child[1] = -1;
            cnt = 0;
        }
    };
    vector<Node> nodes;
    Trie() {
        nodes.emplace_back(); // root at index 0
    }

    void insert(int x) {
        int node = 0;
        nodes[node].cnt++;
        for (int i = 29; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (nodes[node].child[bit] == -1) {
                nodes[node].child[bit] = nodes.size();
                nodes.emplace_back();
            }
            node = nodes[node].child[bit];
            nodes[node].cnt++;
        }
    }

    bool erase(int x) {
        if (nodes[0].cnt == 0) return false;
        int node = 0;
        int path[31];
        path[0] = 0;
        for (int i = 29; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int nxt = nodes[node].child[bit];
            if (nxt == -1 || nodes[nxt].cnt == 0) {
                return false;
            }
            node = nxt;
            path[30 - i] = node;
        }
        for (int i = 0; i <= 30; i++) {
            nodes[path[i]].cnt--;
        }
        return true;
    }

    int kth(int k, int xor_tag) {
        if (k > nodes[0].cnt) return -1;
        int node = 0;
        int ans = 0;
        for (int i = 29; i >= 0; i--) {
            int b = (xor_tag >> i) & 1;
            int pref = b;
            int other = pref ^ 1;
            int pref_child = nodes[node].child[pref];
            int pref_cnt = (pref_child != -1) ? nodes[pref_child].cnt : 0;
            if (pref_cnt >= k) {
                node = pref_child;
            } else {
                if (pref_child != -1) k -= pref_cnt;
                node = nodes[node].child[other];
                ans |= (1 << i);
            }
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    while (cin >> Q) {
        Trie trie;
        int xor_tag = 0;
        while (Q--) {
            int t, k;
            cin >> t >> k;
            if (t == 1) {
                trie.insert(k ^ xor_tag);
            } else if (t == 2) {
                if (!trie.erase(k ^ xor_tag)) {
                    cout << "HEHE\n";
                }
            } else if (t == 3) {
                int ans = trie.kth(k, xor_tag);
                if (ans == -1) {
                    cout << "QQ\n";
                } else {
                    cout << ans << '\n';
                }
            } else { // t == 4
                xor_tag ^= k;
            }
        }
    }
    return 0;
}

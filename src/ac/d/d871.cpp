#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;          // index of the next word
    int add;         // length contributed by the next word
};

int n;
vector<string> words;
vector<vector<Edge>> adj;

/* ---------- find smallest admissible overlap ---------- */
int smallest_overlap(const string& a, const string& b) {
    int la = (int)a.size(), lb = (int)b.size();
    int limit = min(la, lb) - 1;          // must be proper overlap
    for (int k = 1; k <= limit; ++k) {
        bool ok = true;
        for (int i = 0; i < k; ++i) {
            if (a[la - k + i] != b[i]) { ok = false; break; }
        }
        if (ok) return k;
    }
    return 0;    // no admissible overlap
}

/* ---------- memoisation key ---------- */
struct Key {
    uint64_t v;
    bool operator==(const Key& other) const { return v == other.v; }
};
struct KeyHash {
    size_t operator()(const Key& k) const noexcept {
        return std::hash<uint64_t>()(k.v);
    }
};

unordered_map<Key, int, KeyHash> memo;

/* ---------- depth‑first search ---------- */
int dfs(int last, uint32_t onceMask, uint32_t twiceMask) {
    uint64_t keyVal = ( (uint64_t)last << 40 ) |
                      ( (uint64_t)onceMask << 20 ) |
                      (uint64_t)twiceMask;
    Key key{keyVal};
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;

    int best = 0;
    for (const Edge& e : adj[last]) {
        int nxt = e.to;
        if ( (twiceMask >> nxt) & 1u ) continue;          // already twice

        uint32_t nOnce = onceMask, nTwice = twiceMask;
        if ( (onceMask >> nxt) & 1u )
            nTwice |= (1u << nxt);                        // second use
        else
            nOnce  |= (1u << nxt);                        // first use

        int cand = e.add + dfs(nxt, nOnce, nTwice);
        if (cand > best) best = cand;
    }
    memo[key] = best;
    return best;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n) {
        words.assign(n, "");
        for (int i = 0; i < n; ++i) cin >> words[i];
        char startChar;  cin >> startChar;

        /* build adjacency list (including self‑loops) */
        adj.assign(n, {});
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int k = smallest_overlap(words[i], words[j]);
                if (k > 0) {
                    int add = (int)words[j].size() - k;
                    adj[i].push_back({j, add});
                }
            }
        }

        int answer = 0;
        memo.clear();

        for (int i = 0; i < n; ++i) {
            if (!words[i].empty() && words[i][0] == startChar) {
                uint32_t onceMask = 1u << i;
                uint32_t twiceMask = 0;
                int total = (int)words[i].size() + dfs(i, onceMask, twiceMask);
                if (total > answer) answer = total;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}

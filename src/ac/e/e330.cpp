#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <utility>

using namespace std;

struct Key {
    int w, l, r;
    bool operator==(const Key& other) const {
        return w == other.w && l == other.l && r == other.r;
    }
};

struct KeyHash {
    size_t operator()(const Key& k) const noexcept {
        uint64_t h = static_cast<uint64_t>(k.w);
        h = h * 1000003ULL ^ static_cast<uint64_t>(k.l);
        h = h * 1000003ULL ^ static_cast<uint64_t>(k.r);
        // splitmix64
        h ^= h >> 33;
        h *= 0xff51afd7ed558ccdULL;
        h ^= h >> 33;
        h *= 0xc4ceb9fe1a85ec53ULL;
        h ^= h >> 33;
        return static_cast<size_t>(h);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    bool firstCase = true;
    while (cin >> n) {
        vector<int> weight(n + 1);
        for (int i = 1; i <= n; ++i) cin >> weight[i];

        vector<int> left(n + 1), right(n + 1);
        for (int i = 1; i <= n; ++i) {
            int l, r;
            cin >> l >> r;
            left[i] = (l == -1 ? 0 : l);
            right[i] = (r == -1 ? 0 : r);
        }

        // Post-order traversal (iterative)
        vector<int> post;
        post.reserve(n);
        vector<pair<int, char>> st;
        st.reserve(n + 5);
        st.emplace_back(1, 0);
        while (!st.empty()) {
            auto [u, state] = st.back();
            st.pop_back();
            if (u == 0) continue;
            if (state == 0) {
                st.emplace_back(u, 1);
                if (left[u]) st.emplace_back(left[u], 0);
            } else if (state == 1) {
                st.emplace_back(u, 2);
                if (right[u]) st.emplace_back(right[u], 0);
            } else {
                post.push_back(u);
            }
        }

        vector<int> sz(n + 1), normalID(n + 1), mirrorID(n + 1);
        normalID[0] = mirrorID[0] = 0;
        sz[0] = 0;

        unordered_map<Key, int, KeyHash> mp;
        mp.reserve(2 * n);
        mp.max_load_factor(0.7);
        int nextID = 1;

        for (int u : post) {
            int l = left[u], r = right[u];
            sz[u] = 1 + sz[l] + sz[r];

            Key nKey{weight[u], normalID[l], normalID[r]};
            auto it = mp.find(nKey);
            if (it == mp.end()) {
                normalID[u] = nextID;
                mp.emplace(nKey, nextID);
                ++nextID;
            } else {
                normalID[u] = it->second;
            }

            Key mKey{weight[u], mirrorID[r], mirrorID[l]};
            it = mp.find(mKey);
            if (it == mp.end()) {
                mirrorID[u] = nextID;
                mp.emplace(mKey, nextID);
                ++nextID;
            } else {
                mirrorID[u] = it->second;
            }
        }

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (normalID[i] == mirrorID[i] && sz[i] > ans) {
                ans = sz[i];
            }
        }

        if (!firstCase) cout << '\n';
        firstCase = false;
        cout << ans << '\n';
    }
    return 0;
}

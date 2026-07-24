#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (!(cin >> N)) return 0;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // parent[value] = parent value, -1 for root
    unordered_map<int, int> parent;
    // whether a node already has a left/right child
    unordered_map<int, bool> hasLeft, hasRight;

    set<int> inserted;   // ordered set of already inserted values

    // insert from last to first
    for (int i = N - 1; i >= 0; --i) {
        int x = a[i];
        if (inserted.empty()) {
            parent[x] = -1;               // root
            inserted.insert(x);
            continue;
        }

        auto it = inserted.lower_bound(x);
        int pred = -1, succ = -1;

        if (it != inserted.begin()) {
            auto itPred = it;
            --itPred;
            pred = *itPred;
        }
        if (it != inserted.end()) {
            succ = *it;
        }

        // decide parent
        if (pred != -1 && !hasRight[pred]) {
            parent[x] = pred;
            hasRight[pred] = true;
        } else {
            // must use succ
            parent[x] = succ;
            hasLeft[succ] = true;
        }

        inserted.insert(x);
    }

    // collect keys and sort
    vector<int> keys;
    keys.reserve(N);
    for (int v : a) keys.push_back(v);
    sort(keys.begin(), keys.end());
    keys.erase(unique(keys.begin(), keys.end()), keys.end());

    for (int v : keys) {
        cout << v << ' ' << parent[v] << "\n";
    }
    return 0;
}

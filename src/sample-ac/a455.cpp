#include <bits/stdc++.h>
using namespace std;

static int M, N;
static vector<long long> boxCap;          // descending
static vector<long long> allItems;        // ascending (lightest first)

// data used by one feasibility test
static vector<long long> items;           // current k items, descending
static vector<long long> suffixSum;       // suffix sums of items
static vector<long long> remCap;          // remaining capacities of boxes
static long long totalRem;
static int K;                             // number of items in current test

bool dfs(int idx) {
    if (idx == K) return true;                     // all items placed
    if (suffixSum[idx] > totalRem) return false;   // not enough total space

    long long w = items[idx];
    long long lastTried = -1;                      // skip equal capacities

    for (int i = 0; i < M; ++i) {
        if (remCap[i] >= w && remCap[i] != lastTried) {
            long long old = remCap[i];
            remCap[i] -= w;
            totalRem -= w;
            if (dfs(idx + 1)) return true;
            remCap[i] = old;
            totalRem += w;
            lastTried = old;
            if (old == w) break;                  // exact fit – stop trying others
        }
    }
    return false;
}

// test whether the k lightest items can be packed
bool feasible(int k) {
    if (k == 0) return true;
    K = k;
    items.assign(allItems.begin(), allItems.begin() + k);
    sort(items.begin(), items.end(), greater<long long>()); // descending

    suffixSum.assign(K + 1, 0);
    for (int i = K - 1; i >= 0; --i)
        suffixSum[i] = suffixSum[i + 1] + items[i];

    remCap = boxCap;                 // copy capacities (already descending)
    totalRem = 0;
    for (long long c : remCap) totalRem += c;

    if (suffixSum[0] > totalRem) return false; // quick total‑weight test
    return dfs(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> M >> N) {
        boxCap.resize(M);
        for (int i = 0; i < M; ++i) cin >> boxCap[i];
        sort(boxCap.begin(), boxCap.end(), greater<long long>());

        allItems.resize(N);
        for (int i = 0; i < N; ++i) cin >> allItems[i];
        sort(allItems.begin(), allItems.end()); // ascending (lightest first)

        int lo = 0, hi = N;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (feasible(mid))
                lo = mid;
            else
                hi = mid - 1;
        }
        cout << lo << '\n';
    }
    return 0;
}

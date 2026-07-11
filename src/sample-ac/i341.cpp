#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

struct Fenwick {
    int n;
    vector<int> tree;
    Fenwick(int size) : n(size), tree(size + 1, 0) {}
    void add(int i, int delta) {
        for (++i; i <= n; i += i & -i) tree[i] += delta;
    }
    int query(int i) {
        int s = 0;
        for (++i; i > 0; i -= i & -i) s += tree[i];
        return s;
    }
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
    void clear() {
        fill(tree.begin(), tree.end(), 0);
    }
};

ll solve_dc(int L, int R, const vector<int>& P, ll K, vector<ll>& arr1, vector<ll>& arr2, vector<ll>& arr3, vector<ll>& arr4, Fenwick& bit) {
    if (L == R) return 1;
    int mid = (L + R) / 2;
    ll res = solve_dc(L, mid, P, K, arr1, arr2, arr3, arr4, bit) + solve_dc(mid + 1, R, P, K, arr1, arr2, arr3, arr4, bit);

    int lenL = mid - L + 1;
    int lenR = R - mid;

    // Precompute left arrays
    // arr1[i] = maxL[i] - minL[i] + i
    // arr2[i] = maxL[i] + i
    // arr3[i] = -minL[i] + i
    // arr4[i] = i
    // We use 0-based indexing for storage relative to L? No, absolute index is fine.
    // But for vectors, we map L..mid to 0..lenL-1.
    
    vector<int> maxL(lenL), minL(lenL);
    maxL[0] = P[mid];
    minL[0] = P[mid];
    for (int i = 1; i < lenL; ++i) {
        maxL[i] = max(maxL[i-1], P[mid - i]);
        minL[i] = min(minL[i-1], P[mid - i]);
    }

    for (int i = 0; i < lenL; ++i) {
        int idx = mid - i;
        arr1[idx] = (ll)maxL[i] - minL[i] + idx;
        arr2[idx] = (ll)maxL[i] + idx;
        arr3[idx] = (ll)-minL[i] + idx;
        arr4[idx] = (ll)idx;
    }

    // Precompute right arrays (just maxR, minR)
    vector<int> maxR(lenR), minR(lenR);
    maxR[0] = P[mid + 1];
    minR[0] = P[mid + 1];
    for (int i = 1; i < lenR; ++i) {
        maxR[i] = max(maxR[i-1], P[mid + 1 + i]);
        minR[i] = min(minR[i-1], P[mid + 1 + i]);
    }

    // Queries structure: {threshold, l, r, id}
    // We will process 4 types.
    // To avoid storing all queries, we can process type by type.
    // But we need to accumulate results.
    // Let's create a helper lambda to process one type.
    
    auto process_type = [&](int type, const vector<ll>& Arr) -> ll {
        vector<pair<ll, int>> points;
        points.reserve(lenL);
        for (int i = 0; i < lenL; ++i) {
            int idx = mid - i;
            points.push_back({Arr[idx], idx});
        }
        sort(points.begin(), points.end());

        struct Query {
            ll threshold;
            int l, r;
            int id; // not needed if we sum directly
        };
        vector<Query> queries;
        queries.reserve(lenR);

        for (int j = 0; j < lenR; ++j) {
            int r_idx = mid + 1 + j;
            int A = maxR[j];
            int B = minR[j];
            ll C = K + r_idx;
            
            // Find cutoffs in left part (indices in [L, mid])
            // maxL[i] >= A. maxL is non-increasing with i (as i increases from L to mid, range shrinks, max decreases).
            // Wait, our maxL array is indexed by distance from mid.
            // maxL[dist] corresponds to i = mid - dist.
            // As dist increases (i decreases), maxL increases.
            // So maxL[i] is non-decreasing as i decreases (L <- mid).
            // So maxL[i] is non-increasing as i increases (L -> mid).
            // We need largest i such that maxL[i] >= A?
            // Since maxL is non-increasing with i, the condition holds for i in [L, idx_max].
            // Find idx_max: the largest index in [L, mid] such that maxL[idx_max] >= A.
            // We can binary search or two pointers. Since j increases, A increases, so idx_max decreases.
            
            // Similarly for minL: minL[i] is non-decreasing with i.
            // Condition minL[i] <= B holds for i in [L, idx_min].
            // As j increases, B decreases, so idx_min decreases.
            
            // We'll compute these cutoffs outside and pass them? 
            // Or recompute inside. Since we are inside process_type, we don't have A, B easily without looping j again.
            // Better: Generate queries for all 4 types in one pass over j, store them in 4 vectors, then process each vector.
            return 0; 
        }
        return 0;
    };

    // Let's refactor: Generate all queries first.
    struct Q {
        ll val;
        int l, r;
    };
    vector<Q> q1, q2, q3, q4;

    int ptr_max = lenL - 1; // Corresponds to i = L. maxL[lenL-1] is max(L..mid).
    int ptr_min = lenL - 1;

    // Actually, let's use direct index i in [L, mid].
    // maxL_val(i) = max(P[i..mid]).
    // As i increases, maxL_val(i) non-increasing.
    // We need cutoff idx_max: maxL_val(i) >= A for i <= idx_max.
    // Since A increases with j, idx_max decreases.
    // Start idx_max at mid.
    int idx_max = mid;
    int idx_min = mid;

    for (int j = 0; j < lenR; ++j) {
        int A = maxR[j];
        int B = minR[j];
        ll C = K + (mid + 1 + j);

        // Adjust idx_max
        while (idx_max >= L) {
            int cur_max = -1;
            // Efficiently get max(L..mid)? No, we have precomputed maxL.
            // maxL array index: dist = mid - idx_max.
            if (maxL[mid - idx_max] >= A) break;
            idx_max--;
        }
        // Now for i in [L, idx_max], maxL[i] >= A. For i > idx_max, maxL[i] < A.

        // Adjust idx_min
        while (idx_min >= L) {
            if (minL[mid - idx_min] <= B) break;
            idx_min--;
        }
        // Now for i in [L, idx_min], minL[i] <= B. For i > idx_min, minL[i] > B.

        int cut1 = min(idx_max, idx_min);
        if (cut1 >= L) {
            q1.push_back({C, L, cut1});
        }

        if (idx_max > idx_min) {
            int l2 = idx_min + 1;
            int r2 = idx_max;
            if (l2 <= r2) q2.push_back({C + B, l2, r2});
        }

        if (idx_min > idx_max) {
            int l3 = idx_max + 1;
            int r3 = idx_min;
            if (l3 <= r3) q3.push_back({C - A, l3, r3});
        }

        int l4 = max(idx_max, idx_min) + 1;
        int r4 = mid;
        if (l4 <= r4) {
            q4.push_back({C - A + B, l4, r4});
        }
    }

    auto run_queries = [&](vector<Q>& qs, const vector<ll>& Arr) -> ll {
        if (qs.empty()) return 0;
        vector<pair<ll, int>> points;
        points.reserve(lenL);
        for (int i = 0; i < lenL; ++i) {
            points.push_back({Arr[mid - i], mid - i});
        }
        sort(points.begin(), points.end());
        sort(qs.begin(), qs.end(), [](const Q& a, const Q& b) {
            return a.val < b.val;
        });

        ll count = 0;
        int p_idx = 0;
        bit.clear();
        // Bit size should be at least R+1. We pass N.
        for (const auto& q : qs) {
            while (p_idx < (int)points.size() && points[p_idx].first <= q.val) {
                bit.add(points[p_idx].second, 1);
                p_idx++;
            }
            count += bit.query(q.l, q.r);
        }
        return count;
    };

    res += run_queries(q1, arr1);
    res += run_queries(q2, arr2);
    res += run_queries(q3, arr3);
    res += run_queries(q4, arr4);

    return res;
}

void solve() {
    int N;
    ll K;
    if (!(cin >> N >> K)) return;
    vector<int> P(N);
    for (int i = 0; i < N; ++i) cin >> P[i];

    vector<ll> arr1(N), arr2(N), arr3(N), arr4(N);
    Fenwick bit(N + 1);
    cout << solve_dc(0, N - 1, P, K, arr1, arr2, arr3, arr4, bit) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
